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
    // Initialize food categories, etc.
}

void NutritionServer::receiveUserInfo(const User &user)
{
    users_.push_back(user);
    std::ostringstream oss;
    oss << "Received info for user: " << user.getName();
    logInfo(oss.str());
}

void NutritionServer::generateDietPlan(const User &user)
{
    DietPlan plan;
    plan.createPlan(user, foodCategories_);
    // Save or send the plan (stubbed)
    logInfo("Generated diet plan for user: " + user.getName());
}

void NutritionServer::logInfo(const std::string &info)
{
    logger_.log(info);
}

void NutritionServer::analyzeData()
{
    statistics_.analyze(users_);
    statistics_.saveStatistics("data/logs/statistics.txt");
}
