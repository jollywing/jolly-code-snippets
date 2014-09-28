/* Implement parallel processing with select function */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "rio.h"

typedef struct sockaddr SA;
#define LISTENQ 1024
#define MAXLINE 1024
int byte_cnt = 0;

typedef struct {
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} Pool;

int open_listenfd(int port)
{
    /* create socket descriptor */
    int listenfd;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    /* fill server socket address */
    struct sockaddr_in serveraddr;
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    /* INADDR_ANY: any address of this machine */
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);

    /* bind */
    if(bind(listenfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0)
        return -1;

    /* listen */
    if(listen(listenfd, LISTENQ) < 0)
        return -1;

    return listenfd;
}

void init_pool(int listenfd, Pool *p)
{
    /* Initially, there are no connected descriptors */
    int i;
    p->maxi = -1;
    for(i = 0; i < FD_SETSIZE; i++)
        p->clientfd[i] = -1;

    /* Initially, listenfd is only member of select read set */
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, Pool *p)
{
    int i;
    p->nready--;
    for(i = 0; i < FD_SETSIZE; i++){
        if(p->clientfd[i] < 0){
            /* add connected descriptor to the pool */
            p->clientfd[i] = connfd;
            rio_readinitb(&p->clientrio[i], connfd);
            /* add the descriptor to descriptor set */
            FD_SET(connfd, &p->read_set);

            if(connfd > p->maxfd)
                p->maxfd = connfd;
            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    }

    if(i == FD_SETSIZE){
        fprintf(stderr, "add_client error: too many clients!\n");
        exit(1);
    }
}

void check_clients(Pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for(i = 0; (i <= p->maxi) && (p->nready > 0); i++){
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))){
            p->nready --;
            if((n = rio_readlineb(&rio, buf, MAXLINE)) != 0 ){
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d\n",
                        n, byte_cnt, connfd);
                rio_writen(connfd, buf, n);
            }
            else {
                close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}

int main(int argc, char **argv)
{
    int port, listenfd, connfd;
    struct sockaddr_in clientaddr;
    int clientlen = sizeof(struct sockaddr_in);
    Pool pool;

    if(argc != 2){
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);

    listenfd = open_listenfd(port);
    init_pool(listenfd, &pool);
    while(1){
        /* wait for listening/connected descriptors to become ready */
        pool.ready_set = pool.read_set;
        pool.nready = select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

        /* If listening descriptor become ready, add new client to pool */
        if(FD_ISSET(listenfd, &pool.ready_set)){
            connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        /* echo a textline from each ready connected descriptor */
        check_clients(&pool);
    }
    return 0;
}
