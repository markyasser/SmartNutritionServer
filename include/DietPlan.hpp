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

    nlohmann::json toJson();
    std::vector<DayMeals> getWeeklyPlan() const;
    void setFeedback(int feedback);
    int getFeedback() const;

private:
    int id;
    int feedback; // 0 to 5 rating to the plan given by the user
    double bmr;   // Basal Metabolic Rate
    double bmi;   // Body Mass Index
    double dailyCalories;
    std::vector<DayMeals> weeklyPlan;

    // Utility functions
    double calculateNeededCarbs(bool isDiabetic);
    double calculateNeededProtein();
    double calculateNeededSweets(bool isDiabetic);
    double calculateNeededVeggies(bool isHighBloodPressure);
    double calculateBMR(const User &user);
    void assignMeals(std::vector<FoodItem *> &meal, const std::vector<FoodItem *> &availableItems, double neededCarbs, double neededProtein, double neededSweets, double neededVeggies);
};
