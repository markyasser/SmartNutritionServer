#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <netinet/in.h>

class SocketServer {
public:
    SocketServer(int port);
    ~SocketServer();
    void start();
    void stop();
    void handleClient(int clientSocket);

private:
    int serverSocket;
    int port;
    bool running;
    struct sockaddr_in serverAddr;
    std::vector<std::thread> clientThreads;
};