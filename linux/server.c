#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>

typedef struct sockaddr SA;
#define LISTENQ 1024

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

int main(int argc, char *argv[])
{
    /* open listen fd */
    int listenfd = open_listenfd(6000);
    if (listenfd < 0)
        return -1;
    /* accept */
    int connfd;
    // struct sockaddr addr;
    // socklen_t len;
    if(connfd = accept(listenfd, NULL, NULL) > 0){
        printf("[server] conn fd: %d\n", connfd);
        char buf[512];
        int size;
        while(1){
            bzero(buf, 512);
            /* receive data */
            size = recvfrom(connfd, buf, 512, MSG_WAITALL, NULL, NULL);
            /* echo data */
            if(size > 0){
                printf("Your input is: %s\n", buf);
            }
        }
    }
    return 0;
}
