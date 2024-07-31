#include "FoodCategory.hpp"

FoodCategory::FoodCategory(const std::string &name) : name_(name) {}

void FoodCategory::addFoodItem(const std::string &item)
{
    foodItems_.push_back(item);
}

std::vector<std::string> FoodCategory::getFoodItems() const
{
    return foodItems_;
}
