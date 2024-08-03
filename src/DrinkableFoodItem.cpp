#include "DrinkableFoodItem.hpp"

DrickableFoodItem::DrickableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInMilliliters)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantityInMilliliters_(quantityInMilliliters)
{
}

int DrickableFoodItem::getQuantityInMilliliters() const
{
    return quantityInMilliliters_;
}

DrickableFoodItem *DrickableFoodItem::fromJson(const std::string &name, const nlohmann::json &j)
{
    FoodItem base = FoodItem::fromJson(name, j); // Extract common attributes
    int quantityInMilliliters = j.at("quantity").get<int>();

    return new DrickableFoodItem(base.getName(), base.getCalories(), base.getCarbs(), base.getProtein(), base.getFat(), base.getMeal(), base.getType(), quantityInMilliliters);
}

nlohmann::json DrickableFoodItem::toJson() const
{
    nlohmann::json baseJson = FoodItem::toJson(); // Get common attributes
    baseJson["quantity"] = quantityInMilliliters_;

    return baseJson;
}