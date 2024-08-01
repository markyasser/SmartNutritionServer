#include "SocketServer.hpp"

int main()
{
    // Create a server instance on port 3000
    SocketServer server(3000);

    // Start the server
    server.start();

    // Stop the server when done (this line may not be reached if the server runs indefinitely)
    server.stop();

    return 0;
}
