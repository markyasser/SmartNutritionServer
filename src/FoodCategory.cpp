#include "FoodCategory.hpp"

FoodCategory::FoodCategory(const std::string &name, const std::vector<std::string> &foodItems) : name_(name), foodItems_(foodItems) {}

void FoodCategory::addFoodItem(const std::string &item)
{
    foodItems_.push_back(item);
}

std::string FoodCategory::getName() const
{
    return name_;
}
std::vector<std::string> FoodCategory::getItems() const
{
    return foodItems_;
}
