
#include "csapp.h"              /* find csapp.h */
void echo(int connfd);          /* find definition of echo */

void sigchld_handler(int sig)
{
    /* man waitpid */
    while(waitpid(-1, 0, WNOHANG) > 0)
        ;
    return;
}

int main(int argc, char *argv[])
{
    /* the listening file descriptor of server */
    int listenfd;
    /* the connection file descriptor of server */
    int connfd;
    int port;
    /* man sockaddr_in */
    int clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;

    if(argc != 2){
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    port = atoi(argv[1]);
    /* man Signal */
    Signal(SIGCHLD, sigchld_handler);

    /* man open_listenfd */
    listenfd = Open_listenfd(port);

    while(1){
        /* man accept */
        /* man SA */
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

        /* man fork */
        if(fork() == 0) {
            Close(listenfd);
            echo(connfd);
            close(connfd);
            exit(0);
        }
        /* man close */
        Close(connfd);
    }
    return 0;
}

/**
 * server
 * listen socket
 * on receive request
 * fork a thread to response
 */
