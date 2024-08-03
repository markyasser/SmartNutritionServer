#include "DietPlan.hpp"
#include <algorithm>
#include <random>
#include <iostream>

DietPlan::DietPlan() : weeklyPlan(7)
{
    id = 0; // must be incremented by the server
    feedback = 0;
}

void DietPlan::createPlan(const User &user, const std::vector<FoodItem *> &foodItems)
{
    // Calculate needed calories
    bmr = calculateBMR(user);
    dailyCalories = bmr * user.getSedentaryActivityLevel();
    bmi = (user.getWeight() / user.getHeight() / user.getHeight()) * 10000;
    // Calculate ideal body weight

    // Calculate needed carbs
    double neededCarbs = calculateNeededCarbs(user.IsDiabetic());

    // Calculate needed protein
    double neededProtein = calculateNeededProtein();

    // Calculate needed sweets
    double neededSweets = calculateNeededSweets(user.IsDiabetic());

    // Calculate needed veggies
    double neededVeggies = calculateNeededVeggies(user.IsHighBloodPressure());

    // Create a one-week diet plan for the user
    // Separate food items by meal type
    std::vector<FoodItem *> breakfastItems;
    std::vector<FoodItem *> lunchItems;
    std::vector<FoodItem *> dinnerItems;

    std::vector<FoodItem *> filteredItems;
    std::set<std::string> excludedFoods = user.getExcludedFoods();
    for (const auto &item : foodItems)
    {
        if (excludedFoods.find(item->getName()) == excludedFoods.end())
        {
            filteredItems.push_back(item);
        }
    }
    for (const auto &item : filteredItems)
    {
        if (item->getMeal() == "breakfast")
        {
            breakfastItems.push_back(item);
        }
        else if (item->getMeal() == "lunch")
        {
            lunchItems.push_back(item);
        }
        else if (item->getMeal() == "dinner")
        {
            dinnerItems.push_back(item);
        }
    }

    // Distribute nutritional needs
    double breakfastRatio = 0.2; // 20% for breakfast
    double lunchRatio = 0.5;     // 50% for lunch
    double dinnerRatio = 0.3;    // 30% for dinner

    int day = 1;
    for (auto &dayMeals : weeklyPlan)
    {
        dayMeals.day = day++;
        // Assign breakfast items considering nutritional needs
        assignMeals(dayMeals.breakfast, breakfastItems, neededCarbs * breakfastRatio, neededProtein * breakfastRatio, neededSweets * breakfastRatio, neededVeggies * breakfastRatio);

        // Assign lunch items considering nutritional needs
        assignMeals(dayMeals.lunch, lunchItems, neededCarbs * lunchRatio, neededProtein * lunchRatio, neededSweets * breakfastRatio, neededVeggies * breakfastRatio);

        // Assign dinner items considering nutritional needs
        assignMeals(dayMeals.dinner, dinnerItems, neededCarbs * dinnerRatio, neededProtein * dinnerRatio, neededSweets * breakfastRatio, neededVeggies * breakfastRatio);
    }
}
void DietPlan::assignMeals(std::vector<FoodItem *> &meal, const std::vector<FoodItem *> &availableItems, double neededCarbs, double neededProtein, double neededSweets, double neededVeggies)
{
    double totalCarbs = 0;
    double totalProtein = 0;

    // Use a random number generator for variety
    std::mt19937 rng(std::random_device{}());
    std::vector<FoodItem *> candidates = availableItems;

    while (totalCarbs < neededCarbs && totalProtein < neededProtein && !candidates.empty())
    {
        std::uniform_int_distribution<std::size_t> dist(0, candidates.size() - 1);
        std::size_t index = dist(rng);
        FoodItem *selected = candidates[index];

        // Check if adding this item exceeds the nutritional needs
        if (totalCarbs + selected->getCarbs() <= neededCarbs && totalProtein + selected->getProtein() <= neededProtein)
        {
            meal.push_back(selected);
            totalCarbs += selected->getCarbs();
            totalProtein += selected->getProtein();
        }

        // Remove the selected item from the pool of candidates
        candidates.erase(candidates.begin() + index);
    }
}

double DietPlan::calculateNeededCarbs(bool isDiabetic)
{
    double neededCarbs = dailyCalories * 0.50 / 4; // 50% of calories from carbs, 4 cal/g

    if (isDiabetic)
        neededCarbs *= 0.8; // Reduce carb intake for diabetics

    return neededCarbs;
}

double DietPlan::calculateNeededProtein()
{
    double neededProtein = dailyCalories * 0.2 / 4; // 20% of calories from protein, 4 cal/g
    return neededProtein;
}

double DietPlan::calculateNeededSweets(bool isDiabetic)
{
    double neededSweets = dailyCalories * 0.05 / 4; // 5% of calories from sweets, 4 cal/g
    if (isDiabetic)
        return 0.7 * neededSweets; // Reduce sweets intake for diabetics

    return neededSweets;
}

double DietPlan::calculateNeededVeggies(bool isHighBloodPressure)
{
    double neededVeggies = dailyCalories * 0.10 / 4; // 10% of calories from veggies, 4 cal/g

    if (isHighBloodPressure)
        neededVeggies *= 1.2; // increase veggies for high blood pressure
    return neededVeggies;
}

double DietPlan::calculateBMR(const User &user)
{
    // Basic formula for calculating daily caloric needs
    double weight = user.getWeight(); // in kg
    double height = user.getHeight(); // in cm
    int age = user.getAge();

    double bmr; // Basal Metabolic Rate
    if (user.getGender() == "male")
    {
        bmr = 10 * weight + 6.25 * height - 5 * age + 5;
    }
    else
    {
        bmr = 10 * weight + 6.25 * height - 5 * age - 161;
    }

    // Assume a sedentary activity level as a default
    return bmr;
}

nlohmann::json DietPlan::toJson()
{
    nlohmann::json j;
    j["id"] = id;
    j["bmr"] = bmr;
    j["dailyCalories"] = dailyCalories;
    j["bmi"] = bmi;
    // Create a JSON array for the weekly plan
    j["weeklyPlan"] = nlohmann::json::array();
    for (const auto &dayMeals : weeklyPlan)
    {
        nlohmann::json dayJson;
        dayJson["day"] = dayMeals.day;
        // Convert breakfast items to JSON
        dayJson["breakfast"] = nlohmann::json::array();
        for (const auto &item : dayMeals.breakfast)
        {
            dayJson["breakfast"].push_back(item->toJson());
        }

        // Convert lunch items to JSON
        dayJson["lunch"] = nlohmann::json::array();
        for (const auto &item : dayMeals.lunch)
        {
            dayJson["lunch"].push_back(item->toJson());
        }

        // Convert dinner items to JSON
        dayJson["dinner"] = nlohmann::json::array();
        for (const auto &item : dayMeals.dinner)
        {
            dayJson["dinner"].push_back(item->toJson());
        }

        // Add the day's plan to the weekly plan
        j["weeklyPlan"].push_back(dayJson);
    }

    return j;
}

std::vector<DayMeals> DietPlan::getWeeklyPlan() const
{
    return weeklyPlan;
}

void DietPlan::setFeedback(int feedback)
{
    this->feedback = feedback;
}

int DietPlan::getFeedback() const
{
    return feedback;
}