#pragma once
#include "User.hpp"
#include "FoodItem.hpp"
#include <vector>
#include <string>
#include <random>

class DietPlan
{
public:
    DietPlan();
    void createPlan(const User &user, const std::vector<FoodItem> &categories);
    void display() const;

private:
    int id;
    std::vector<std::string> breakfast_;
    std::vector<std::string> lunch_;
    std::vector<std::string> dinner_;

    // Utility functions
    std::vector<std::string> getRandomItems(const std::vector<std::string> &items, size_t count);
};
