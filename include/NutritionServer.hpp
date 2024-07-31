#pragma once
#include <vector>
#include "User.hpp"
#include "FoodCategory.hpp"
#include "DietPlan.hpp"
#include "Logger.hpp"
#include "Statistics.hpp"
#include "Observer.hpp"

class NutritionServer : public Observer
{
public:
    static NutritionServer &getInstance();
    void receiveUserInfo(const User &user);
    void generateDietPlan(const User &user);
    void logInfo(const std::string &info);
    void analyzeData();

    // Observer interface
    void update(const std::string &data) override;

private:
    NutritionServer();
    std::vector<User> users_;
    std::vector<FoodCategory> foodCategories_;
    Logger logger_;
    Statistics statistics_;
};
