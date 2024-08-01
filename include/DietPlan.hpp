#pragma once
#include "User.hpp"
#include "FoodItem.hpp"
#include <vector>
#include <string>
#include <random>

// Structure to hold meals for a day
struct DayMeals
{
    std::vector<FoodItem> breakfast;
    std::vector<FoodItem> lunch;
    std::vector<FoodItem> dinner;
};

class DietPlan
{
public:
    DietPlan();
    void createPlan(const User &user, const std::vector<FoodItem> &foodItems);
    void display() const;

private:
    int id;
    std::vector<DayMeals> weeklyPlan;

    // Utility functions
    double calculateNeededCarbs(const User &user);
    double calculateNeededProtein(const User &user);
    double calculateNeededSweets(const User &user);
    double calculateNeededVeggies(const User &user);
    double calculateDailyCalories(const User &user);

    std::vector<FoodItem> getRandomItems(const std::vector<FoodItem> &items, size_t count);
    void assignMeals(std::vector<FoodItem> &meal, const std::vector<FoodItem> &availableItems, double neededCarbs, double neededProtein);
};
