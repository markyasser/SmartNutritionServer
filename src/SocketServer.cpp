#include "SocketServer.hpp"
#include <arpa/inet.h>
#include <unistd.h>

SocketServer::SocketServer(int port) : port(port), running(false) {}

SocketServer::~SocketServer()
{
    stop();
}

void SocketServer::start()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Error binding socket." << std::endl;
        return;
    }

    if (listen(serverSocket, 5) < 0)
    {
        std::cerr << "Error listening on socket." << std::endl;
        return;
    }

    running = true;
    std::cout << "Server started on port " << port << std::endl;

    while (running)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket >= 0)
        {
            clientThreads.emplace_back(&SocketServer::handleClient, this, clientSocket);
        }
    }
}

void SocketServer::stop()
{
    running = false;
    close(serverSocket);
    for (auto &thread : clientThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
    std::cout << "Server stopped." << std::endl;
}

void handleClient(int client_socket)
{
    char buffer[1024] = {0};
    read(client_socket, buffer, sizeof(buffer));
    std::cout << "Received request:\n"
              << buffer << std::endl;

    // Parse the request to determine the response
    std::string request(buffer);
    std::string response;

    if (request.find("GET / HTTP/1.1") != std::string::npos)
    {
        response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, World!";
    }
    else
    {
        response =
            "HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 15\r\n"
            "\r\n"
            "Bad Request";
    }

    send(client_socket, response.c_str(), response.length(), 0);
    close(client_socket);
}