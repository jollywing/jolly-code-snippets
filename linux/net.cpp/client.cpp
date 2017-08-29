
// #include <cstring>
// include iostream, then you can use string
#include <iostream>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

class Client {
private:
    string serverIP;
    short serverPort;
    int sock;

    void Disconnect() {
        close(sock);
        return;
    }

    int Send(string &str) {
        return send(sock, str.c_str(), str.length(), 0);
    }

    int Receive(char * buffer, const unsigned short bufferSize) {
        return recv(sock, buffer, bufferSize - 1, 0);
    }

public:

    Client(const char *ip, int port) {
        serverIP = string(ip);
        serverPort = port;
    }

    void Connect() {
        // new socket
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock < 0) {
            cout << "Create socket failed!" << endl;
            exit(1);
        }
        // make sock addr
        sockaddr_in serverAddr;
        bzero(&serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
        serverAddr.sin_port = htons(serverPort);
        // connect
        int result;
        result = connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
        if (result < 0) {
            cout << "Failed to connnect to server." << endl;
            exit(1);
        }

        cout << "input your message to server, "
                "if you want to exit, input 'bye'" << endl;
        // send / receive loop
        const unsigned short bufferSize = 256;
        char buffer[bufferSize];
        int nBytes;
        while (1) {
            cout << "Your Input: ";
            string str;
            cin >> str;
            if (str.compare("bye") == 0) {
                break;
            }
            Send(str);
            cout << "Server Response: ";
            cout.flush();
            nBytes = Receive(buffer, bufferSize);
            buffer[nBytes] = 0;
            cout << buffer << endl;
        }
        Disconnect();
    }
};

int main()
{
    Client client("localhost", 54321);
    client.Connect();
    return 0;
}
