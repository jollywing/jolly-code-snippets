
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Server {
private:
    short port;
    int sock;
public:
    Server(short port) {
        this->port = port;
    }
    void Listen() {
        // make socket
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock < 0) {
            cout << "create sock failed!" << endl;
        }
        // bind socket
        struct sockaddr_in serverAddr;
        bzero(&serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddr.sin_port = htons(port);

        int result;
        result = bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        if (result < 0) {
            cout << "Failed to bind server socket!" << endl;
            exit(1);
        }

        const unsigned short MAXPENDING = 5;
        result = listen(sock, MAXPENDING);
        if (result < 0) {
            cout << "Failed to listen on server socket!" << endl;
            exit(1);
        }
    }
    ~Server() {
    }
};

int main()
{
    return 0;
}
