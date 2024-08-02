#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <json.hpp>
#include "JsonManager.hpp"
#include "Statistics.hpp"
#include <vector>
#include "User.hpp"
#include "FoodItem.hpp"
#include "DietPlan.hpp"
#include "Logger.hpp"
#include "Feedback.hpp"

// For convenience
using json = nlohmann::json;

class NutritionServer
{
public:
    static NutritionServer &getInstance();
    nlohmann::json generateDietPlan(const User &user);
    nlohmann::json analyzeData();
    nlohmann::json getRating();
    nlohmann::json getFoodItems();
    bool receiveFeedback(int feedback);
    bool receiveUserInfo(const User &user);

    void saveUserInfo(const User &user);
    void logInfo(const std::string &info);
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
