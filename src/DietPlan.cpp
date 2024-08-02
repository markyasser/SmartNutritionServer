#include "DietPlan.hpp"
#include <algorithm>
#include <random>
#include <iostream>

DietPlan::DietPlan() : weeklyPlan(7)
{
    id = 0; // must be incremented by the server
    feedback = 0;
}

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

    // Distribute nutritional needs
    double breakfastRatio = 0.2; // 20% for breakfast
    double lunchRatio = 0.3;     // 30% for lunch
    double dinnerRatio = 0.5;    // 50% for dinner

    int day = 1;
    for (auto &dayMeals : weeklyPlan)
    {
        dayMeals.day = day++;
        // Assign breakfast items considering nutritional needs
        assignMeals(dayMeals.breakfast, breakfastItems, neededCarbs * breakfastRatio, neededProtein * breakfastRatio);

        // Assign lunch items considering nutritional needs
        assignMeals(dayMeals.lunch, lunchItems, neededCarbs * lunchRatio, neededProtein * lunchRatio);

        // Assign dinner items considering nutritional needs
        assignMeals(dayMeals.dinner, dinnerItems, neededCarbs * dinnerRatio, neededProtein * dinnerRatio);
    }
}
void DietPlan::assignMeals(std::vector<FoodItem> &meal, const std::vector<FoodItem> &availableItems, double neededCarbs, double neededProtein)
{
    double totalCarbs = 0;
    double totalProtein = 0;

    // Use a random number generator for variety
    std::mt19937 rng(std::random_device{}());
    std::vector<FoodItem> candidates = availableItems;

    while (totalCarbs < neededCarbs && totalProtein < neededProtein && !candidates.empty())
    {
        std::uniform_int_distribution<std::size_t> dist(0, candidates.size() - 1);
        std::size_t index = dist(rng);
        FoodItem selected = candidates[index];

        // Check if adding this item exceeds the nutritional needs
        if (totalCarbs + selected.getCarbs() <= neededCarbs && totalProtein + selected.getProtein() <= neededProtein)
        {
            meal.push_back(selected);
            totalCarbs += selected.getCarbs();
            totalProtein += selected.getProtein();
        }

        // Remove the selected item from the pool of candidates
        candidates.erase(candidates.begin() + index);
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
        std::cout << "Day " << weeklyPlan[i].day << ":\n";
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

nlohmann::json DietPlan::toJson()
{
    nlohmann::json j;
    j["id"] = id;
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
            dayJson["breakfast"].push_back(item.toJson());
        }

        // Convert lunch items to JSON
        dayJson["lunch"] = nlohmann::json::array();
        for (const auto &item : dayMeals.lunch)
        {
            dayJson["lunch"].push_back(item.toJson());
        }

        // Convert dinner items to JSON
        dayJson["dinner"] = nlohmann::json::array();
        for (const auto &item : dayMeals.dinner)
        {
            dayJson["dinner"].push_back(item.toJson());
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