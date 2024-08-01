#include "DietPlan.hpp"
#include <algorithm>
#include <random>
#include <iostream>

void DietPlan::createPlan(const User &user, const std::vector<FoodCategory> &categories)
{
    plan_.clear();

    // Define the number of items to select from each category
    size_t carbsCount = 2;
    size_t proteinCount = 2;
    size_t sweetsCount = 1;
    size_t veggiesCount = 2;

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    for (const auto &category : categories)
    {
        if (category.getName() == "Carbs")
        {
            auto items = getRandomItems(category.getItems(), carbsCount);
            plan_.insert(plan_.end(), items.begin(), items.end());
        }
        else if (category.getName() == "Protein")
        {
            auto items = getRandomItems(category.getItems(), proteinCount);
            plan_.insert(plan_.end(), items.begin(), items.end());
        }
        else if (category.getName() == "Sweets")
        {
            auto items = getRandomItems(category.getItems(), sweetsCount);
            plan_.insert(plan_.end(), items.begin(), items.end());
        }
        else if (category.getName() == "Veggies")
        {
            auto items = getRandomItems(category.getItems(), veggiesCount);
            plan_.insert(plan_.end(), items.begin(), items.end());
        }
    }
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
    std::cout << "Diet Plan:" << std::endl;
    for (const auto &item : plan_)
    {
        std::cout << item << std::endl;
    }
}