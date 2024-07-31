#pragma once
#include "User.hpp"
#include "FoodCategory.hpp"
#include <vector>

class DietPlan
{
public:
    void createPlan(const User &user, const std::vector<FoodCategory> &categories);
    // Additional methods to retrieve the plan
};
