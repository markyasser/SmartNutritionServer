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
    plan.display();
}

void NutritionServer::logInfo(const std::string &info)
{
    logger_.log(info);
}

void NutritionServer::populateFoodCategories()
{
    // Example categories and items
    foodCategories_.emplace_back("Carbs", std::vector<std::string>{"Rice", "Pasta", "Bread"});
    foodCategories_.emplace_back("Protein", std::vector<std::string>{"Chicken", "Beef", "Tofu"});
    foodCategories_.emplace_back("Sweets", std::vector<std::string>{"Cake", "Ice Cream", "Cookies"});
    foodCategories_.emplace_back("Veggies", std::vector<std::string>{"Carrots", "Broccoli", "Spinach"});
}

void NutritionServer::analyzeData()
{
    statistics_.analyze(users_);
    statistics_.saveStatistics("data/logs/statistics.txt");
    statistics_.display();
}
