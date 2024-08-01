#pragma once
#include <string>
#include <vector>

class FoodCategory
{
public:
    FoodCategory(const std::string &name, const std::vector<std::string> &foodItems);
    void addFoodItem(const std::string &item);
    std::vector<std::string> getItems() const;
    std::string getName() const;

private:
    std::string name_;
    std::vector<std::string> foodItems_;
};
