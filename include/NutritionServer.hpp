#pragma once
#include <vector>
#include "User.hpp"
#include "FoodCategory.hpp"
#include "DietPlan.hpp"
#include "Logger.hpp"
#include "Statistics.hpp"

class NutritionServer
{
public:
    static NutritionServer &getInstance();
    void receiveUserInfo(const User &user);
    void saveUserInfo(const User &user);
    void generateDietPlan(const User &user);
    void logInfo(const std::string &info);
    void analyzeData();
    void populateFoodCategories();

private:
    NutritionServer();
    std::vector<User> users_;
    std::vector<FoodCategory> foodCategories_;
    Logger logger_;
    Statistics statistics_;
    std::string usersFilePath_;
};
