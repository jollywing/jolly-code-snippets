#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h>

#define TRAM_STATUS_ADDR "127.0.0.1"
#define TRAM_STATUS_RECV_PORT 9200

int main(int argc, char **argv)
{
    int fd;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket create failed.");
        return -1;
    }

    struct sockaddr_in mcast_addr;
    memset(&mcast_addr, 0, sizeof(mcast_addr));
    mcast_addr.sin_family = AF_INET;
    mcast_addr.sin_addr.s_addr = inet_addr(TRAM_STATUS_ADDR);
    mcast_addr.sin_port = htons(TRAM_STATUS_RECV_PORT);

    const char msg[32] = "hello, guys";
    if (sendto(fd, msg, sizeof(msg), 0, (struct sockaddr *)&mcast_addr, sizeof(mcast_addr)) < 0)
    {
        perror("sendto");
        return -1;
    }
    printf("send ok!\n");

    setsockopt(fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mcast_addr, sizeof(mcast_addr));
    close(fd);

    return 0;
}
