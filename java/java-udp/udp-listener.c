
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char ** argv)
{
    int port = 8888;
    
    struct sockaddr_in sin;
    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);

    int socket_descriptor;
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socket_descriptor, (struct sockaddr *)&sin, sizeof(sin));

    char message[256];
    
    while(1)
    {
        recvfrom(socket_descriptor, message, sizeof(message),
                 0, (struct sockaddr *)&sin, sizeof(sin));
        printf("%s\n", message);
        if (strcmp(message, "ByeBye") == 0)
        {
            break;
        }
    }

    close(socket_descriptor);
    return 0;
}
