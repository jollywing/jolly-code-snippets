#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct sockaddr SA;

int open_clientfd(char *hostname, int port)
{
    int clientfd;
    /* Get client socket */
    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    /* Get host entry from dns server */
    struct hostent *hp;
    if((hp = gethostbyname(hostname)) == NULL)
        return -2;

    /* Fill server's sockaddr */
    struct sockaddr_in serveraddr;
    bzero((char *)&serveraddr, sizeof(struct sockaddr_in));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)hp->h_addr, (char *)&serveraddr.sin_addr.s_addr,
            hp->h_length);
    serveraddr.sin_port = htons(port);
    if (connect(clientfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
        return -1;

    /* SUCCESS */
    return clientfd;
}

void test_localhost()
{
    int clientfd = open_clientfd("localhost", 6000);
    if(clientfd > 0){
        char buf[512];
        while(1){
            bzero(buf, 512);
            /* read string */
            scanf("%s", buf);
            /* if EOF, then exit while */
            if(buf[0] == 0)
                break;
            /* else send string */
            else {
                if(!strcmp(buf, "exit")){
                    break;
                }
                printf("[client] your input is: %s, size: %d\n", buf, strlen(buf));
                send(clientfd, buf, strlen(buf), 0);
            }
        }
        close(clientfd);
    }
}

int main(int argc, char **argv)
{
    int clientfd = open_clientfd("www.baidu.com", 80);
    if(clientfd > 0){
        printf("connect to website succeed!\n");
        close(clientfd);
    }

    test_localhost();
    return 0;
}
