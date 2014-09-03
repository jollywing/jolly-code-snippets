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
    return 0;
}
