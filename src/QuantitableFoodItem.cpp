#include "QuantitableFoodItem.hpp"

QuantitableFoodItem::QuantitableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantity)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantity_(quantity)
{
}

int QuantitableFoodItem::getQuantity() const
{
    return quantity_;
}