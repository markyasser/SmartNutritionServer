#include "NutritionServer.hpp"
#include <sstream>

NutritionServer &NutritionServer::getInstance()
{
    static NutritionServer instance;
    return instance;
}

NutritionServer::NutritionServer()
    : logger_("data/logs/server_log.txt")
{
    // Initialize food categories
    populateFoodCategories();

    usersFilePath_ = "data/users.txt";
}

void NutritionServer::receiveUserInfo(const User &user)
{
    users_.push_back(user);
    std::ostringstream oss;
    oss << "Received info for user: " << user.getName();
    logInfo(oss.str());
    saveUserInfo(user);
}

void NutritionServer::generateDietPlan(const User &user)
{
    DietPlan plan;
    plan.createPlan(user, foodCategories_);
    // Save or send the plan (stubbed)
    logInfo("Generated diet plan for user: " + user.getName());
    plan.display();
}

void NutritionServer::logInfo(const std::string &info)
{
    logger_.log(info);
}

void NutritionServer::populateFoodCategories()
{
}

void NutritionServer::analyzeData()
{
    statistics_.analyze(users_);
    statistics_.saveStatistics("data/logs/statistics.txt");
    statistics_.display();
}

void NutritionServer::saveUserInfo(const User &user)
{
    std::ofstream outFile(usersFilePath_, std::ios::app);
    if (outFile.is_open())
    {
        outFile << "Name: " << user.getName() << std::endl
                << "Age: " << user.getAge() << ", Gender: " << user.getGender() << std::endl
                << "Weight:" << user.getWeight() << ", Height: " << user.getHeight() << std::endl
                << std::endl;
        outFile.close();
    }
}