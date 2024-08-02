#pragma once
#include "JsonManager.hpp"
#include "Statistics.hpp"
#include <vector>
#include "User.hpp"
#include "FoodItem.hpp"
#include "DietPlan.hpp"
#include "Logger.hpp"
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
    nlohmann::json generateDietPlan(const User &user);
    void logInfo(const std::string &info);
    nlohmann::json analyzeData();
    void populateFoodItems(); // Read from json

private:
    NutritionServer();
    std::vector<User> users_;
    std::vector<FoodItem> foodItems_;
    Logger logger_;
    std::string usersFilePath_;

    // Utility functions
    std::vector<User> loadUsers();
};
