#pragma once
#include "FoodItem.hpp"

class DrickableFoodItem : public FoodItem
{
public:
    DrickableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInMilliliters);

    int getQuantityInMilliliters() const;

private:
    int quantityInMilliliters_;
};
