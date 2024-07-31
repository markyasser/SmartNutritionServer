#include "NutritionServer.hpp"

NutritionServer &NutritionServer::getInstance()
{
    static NutritionServer instance;
    return instance;
}

NutritionServer::NutritionServer()
{
    // Initialize food categories, logger, etc.
}

void NutritionServer::receiveUserInfo(const User &user)
{
    users_.push_back(user);
    logInfo("Received info for user: " + user.getName());
}

void NutritionServer::generateDietPlan(const User &user)
{
    DietPlan plan;
    plan.createPlan(user, foodCategories_);
    // Send plan back to the patient software (stubbed)
}

void NutritionServer::logInfo(const std::string &info)
{
    logger_.log(info);
}

void NutritionServer::analyzeData()
{
    statistics_.analyze(users_);
}

void NutritionServer::update(const std::string &data)
{
    logInfo("Update received: " + data);
}
