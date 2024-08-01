#include "DietPlan.hpp"
#include <algorithm>
#include <random>
#include <iostream>

DietPlan::DietPlan()
{
    id = 0;
}

void DietPlan::createPlan(const User &user, const std::vector<FoodItem> &categories)
{
    // Get user's needed carbs, protein, sweets, veggies from his weight, height, age, IsDiabetic, blood pressure
    double weight = user.getWeight();
    double height = user.getHeight();
    int age = user.getAge();
    bool isDiabetic = user.getIsDiabetic();
    int bloodPressureUpper = user.getBloodPressureUpper();
    int bloodPressureLower = user.getBloodPressureLower();

    // Calculate needed calories

    // Calculate needed carbs

    // Calculate needed protein

    // Calculate needed sweets

    // Calculate needed veggies

    // Create a one-week diet plan for the user
    size_t days = 7;
}

std::vector<std::string> DietPlan::getRandomItems(const std::vector<std::string> &items, size_t count)
{
    std::vector<std::string> result;
    if (items.empty() || count == 0)
        return result;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::string> shuffledItems = items;
    std::shuffle(shuffledItems.begin(), shuffledItems.end(), gen);

    size_t limit = std::min(count, shuffledItems.size());
    result.insert(result.end(), shuffledItems.begin(), shuffledItems.begin() + limit);

    return result;
}

void DietPlan::display() const
{
}