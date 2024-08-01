#pragma once
#include "User.hpp"
#include "FoodCategory.hpp"
#include <vector>
#include <string>
#include <random>

class DietPlan
{
public:
    void createPlan(const User &user, const std::vector<FoodCategory> &categories);
    void display() const;

private:
    std::vector<std::string> plan_;

    // Utility functions
    std::vector<std::string> getRandomItems(const std::vector<std::string> &items, size_t count);
};
