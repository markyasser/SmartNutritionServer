#pragma once
#include <string>
#include <vector>

class FoodCategory
{
public:
    FoodCategory(const std::string &name);
    void addFoodItem(const std::string &item);
    std::vector<std::string> getFoodItems() const;

private:
    std::string name_;
    std::vector<std::string> foodItems_;
};
