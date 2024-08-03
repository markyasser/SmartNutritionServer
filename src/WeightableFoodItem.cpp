#include "WeightableFoodItem.hpp"

WeightableFoodItem::WeightableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInGrams)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantityInGrams_(quantityInGrams)
{
}

int WeightableFoodItem::getQuantityInGrams() const
{
    return quantityInGrams_;
}