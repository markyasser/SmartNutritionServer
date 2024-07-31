#include "User.hpp"
#include "NutritionServer.hpp"

int main(int argc, char *argv[])
{
    NutritionServer &server = NutritionServer::getInstance();

    // Example: Add users and create plans
    User user1("Alice", 25, 65.0, 165.0);
    server.receiveUserInfo(user1);
    server.generateDietPlan(user1);

    User user2("Bob", 30, 75.0, 180.0);
    server.receiveUserInfo(user2);
    server.generateDietPlan(user2);

    // Analyze data
    server.analyzeData();

    return 0;
}
