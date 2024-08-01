#pragma once
#include <vector>
#include "User.hpp"
#include "FoodItem.hpp"
#include "DietPlan.hpp"
#include "Logger.hpp"
#include "Statistics.hpp"
#include <json.hpp>
#include <sstream>
#include <iostream>
#include <fstream>

// For convenience
using json = nlohmann::json;

class NutritionServer
{
public:
    static NutritionServer &getInstance();
    void receiveUserInfo(const User &user);
    void saveUserInfo(const User &user);
    void generateDietPlan(const User &user);
    void logInfo(const std::string &info);
    void analyzeData();
    void populateFoodItems(); // Read from json

private:
    NutritionServer();
    std::vector<User> users_;
    std::vector<FoodItem> foodItems_;
    Logger logger_;
    Statistics statistics_;
    std::string usersFilePath_;
};
