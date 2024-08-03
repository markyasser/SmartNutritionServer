#include "DrinkableFoodItem.hpp"

DrickableFoodItem::DrickableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInMilliliters)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantityInMilliliters_(quantityInMilliliters)
{
}

int DrickableFoodItem::getQuantityInMilliliters() const
{
    return quantityInMilliliters_;
}
