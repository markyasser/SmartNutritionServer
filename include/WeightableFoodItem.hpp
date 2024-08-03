#pragma once
#include "FoodItem.hpp"

class WeightableFoodItem : public FoodItem
{
public:
    WeightableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInGrams);

    int getQuantityInGrams() const;

private:
    int quantityInGrams_;
};
