#include "DietPlan.hpp"
#include <algorithm>
#include <random>
#include <iostream>

DietPlan::DietPlan() : id(0), weeklyPlan(7) {}

void DietPlan::createPlan(const User &user, const std::vector<FoodItem> &foodItems)
{
    // Get user's needed carbs, protein, sweets, veggies from his weight, height, age, IsDiabetic, blood pressure
    double weight = user.getWeight();
    double height = user.getHeight();
    int age = user.getAge();
    bool isDiabetic = user.getIsDiabetic();
    int bloodPressureUpper = user.getBloodPressureUpper();
    int bloodPressureLower = user.getBloodPressureLower();

    // Calculate needed calories
    double dailyCalories = calculateDailyCalories(user);

    // Calculate needed carbs
    double neededCarbs = calculateNeededCarbs(user);

    // Calculate needed protein
    double neededProtein = calculateNeededProtein(user);

    // Calculate needed sweets
    double neededSweets = calculateNeededSweets(user);

    // Calculate needed veggies
    double neededVeggies = calculateNeededVeggies(user);

    // Create a one-week diet plan for the user
    // Separate food items by meal type
    std::vector<FoodItem> breakfastItems;
    std::vector<FoodItem> lunchItems;
    std::vector<FoodItem> dinnerItems;

    for (const auto &item : foodItems)
    {
        if (item.getMeal() == "breakfast")
        {
            breakfastItems.push_back(item);
        }
        else if (item.getMeal() == "lunch")
        {
            lunchItems.push_back(item);
        }
        else if (item.getMeal() == "dinner")
        {
            dinnerItems.push_back(item);
        }
    }

    // Example: Assign random items for each meal type to each day
    for (auto &dayMeals : weeklyPlan)
    {
        // Assign random breakfast items
        dayMeals.breakfast = getRandomItems(breakfastItems, 2); // Example: 2 items for breakfast
        // Assign random lunch items
        dayMeals.lunch = getRandomItems(lunchItems, 2); // Example: 2 items for lunch
        // Assign random dinner items
        dayMeals.dinner = getRandomItems(dinnerItems, 2); // Example: 2 items for dinner
    }
}

std::vector<FoodItem> DietPlan::getRandomItems(const std::vector<FoodItem> &items, size_t count)
{
    std::vector<FoodItem> result;
    std::sample(items.begin(), items.end(), std::back_inserter(result), count, std::mt19937{std::random_device{}()});
    return result;
}

double DietPlan::calculateNeededCarbs(const User &user)
{
    double dailyCalories = calculateDailyCalories(user);
    double neededCarbs = dailyCalories * 0.50 / 4; // 50% of calories from carbs, 4 cal/g

    if (user.getIsDiabetic())
    {
        neededCarbs *= 0.8; // Reduce carb intake for diabetics
    }

    return neededCarbs;
}

double DietPlan::calculateNeededProtein(const User &user)
{
    double dailyCalories = calculateDailyCalories(user);
    double neededProtein = dailyCalories * 0.20 / 4; // 20% of calories from protein, 4 cal/g
    return neededProtein;
}

double DietPlan::calculateNeededSweets(const User &user)
{
    // Assuming a simplified model where sweets are a small percentage of daily calories
    double dailyCalories = calculateDailyCalories(user);
    double neededSweets = dailyCalories * 0.05 / 4; // 5% of calories from sweets, 4 cal/g
    return neededSweets;
}

double DietPlan::calculateNeededVeggies(const User &user)
{
    // Assuming a simplified model where veggies are a percentage of daily calories
    double dailyCalories = calculateDailyCalories(user);
    double neededVeggies = dailyCalories * 0.10 / 4; // 10% of calories from veggies, 4 cal/g
    return neededVeggies;
}

double DietPlan::calculateDailyCalories(const User &user)
{
    // Basic formula for calculating daily caloric needs
    double weight = user.getWeight(); // in kg
    double height = user.getHeight(); // in cm
    int age = user.getAge();

    double bmr;
    if (user.getGender() == "male")
    {
        bmr = 10 * weight + 6.25 * height - 5 * age + 5;
    }
    else
    {
        bmr = 10 * weight + 6.25 * height - 5 * age - 161;
    }

    // Assume a sedentary activity level as a default
    return bmr * 1.2;
}

void DietPlan::display() const
{
    std::cout << "Weekly Diet Plan:\n";
    for (size_t i = 0; i < weeklyPlan.size(); ++i)
    {
        std::cout << "Day " << (i + 1) << ":\n";
        std::cout << "  Breakfast:\n";
        for (const auto &item : weeklyPlan[i].breakfast)
        {
            std::cout << "    " << item.getName() << "\n";
        }
        std::cout << "  Lunch:\n";
        for (const auto &item : weeklyPlan[i].lunch)
        {
            std::cout << "    " << item.getName() << "\n";
        }
        std::cout << "  Dinner:\n";
        for (const auto &item : weeklyPlan[i].dinner)
        {
            std::cout << "    " << item.getName() << "\n";
        }
    }
}