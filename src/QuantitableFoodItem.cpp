#include "QuantitableFoodItem.hpp"

QuantitableFoodItem::QuantitableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantity)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantity_(quantity)
{
}

int QuantitableFoodItem::getQuantity() const
{
    return quantity_;
}

QuantitableFoodItem *QuantitableFoodItem::fromJson(const std::string &name, const nlohmann::json &j)
{
    FoodItem base = FoodItem::fromJson(name, j); // Extract common attributes
    int quantity = j.at("quantity").get<int>();

    return new QuantitableFoodItem(base.getName(), base.getCalories(), base.getCarbs(), base.getProtein(), base.getFat(), base.getMeal(), base.getType(), quantity);
}

nlohmann::json QuantitableFoodItem::toJson() const
{
    nlohmann::json baseJson = FoodItem::toJson(); // Get common attributes
    baseJson["quantity"] = quantity_;

    return baseJson;
}