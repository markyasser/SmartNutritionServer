#pragma once
#include <vector>
#include <string>
#include <random>
#include "User.hpp"
#include "FoodItem.hpp"
#include "User.hpp"

// Structure to hold meals for a day
struct DayMeals
{
    int day;
    std::vector<FoodItem *> breakfast;
    std::vector<FoodItem *> lunch;
    std::vector<FoodItem *> dinner;
};

class DietPlan
{
public:
    DietPlan();
    void createPlan(const User &user, const std::vector<FoodItem *> &foodItems);
    void display() const;

    nlohmann::json toJson();
    std::vector<DayMeals> getWeeklyPlan() const;
    void setFeedback(int feedback);
    int getFeedback() const;

private:
    int id;
    int feedback; // 0 to 5 rating to the plan given by the user
    User user_;
    std::vector<DayMeals> weeklyPlan;

    // Utility functions
    double calculateNeededCarbs(const User &user);
    double calculateNeededProtein(const User &user);
    double calculateNeededSweets(const User &user);
    double calculateNeededVeggies(const User &user);
    double calculateDailyCalories(const User &user);
    void assignMeals(std::vector<FoodItem *> &meal, const std::vector<FoodItem *> &availableItems, double neededCarbs, double neededProtein);
};
