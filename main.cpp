#include <crow.h>
#include "NutritionRoutes.hpp"

int main()
{
    // Create Crow application instance
    crow::SimpleApp app;

    // Create an instance of NutritionServer
    NutritionServer &server = NutritionServer::getInstance();

    // Set up routes using the NutritionRoutes class
    NutritionRoutes::setupRoutes(app, server);

    // Start the server on port 8080 with multithreading enabled
    app.port(8080).multithreaded().run();

    return 0;
}
