#include "DrinkableFoodItem.hpp"

DrinkableFoodItem::DrinkableFoodItem() : FoodItem()
{
}

DrinkableFoodItem::DrinkableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInMilliliters)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantityInMilliliters_(quantityInMilliliters)
{
}

int DrinkableFoodItem::getQuantity() const
{
    return quantityInMilliliters_;
}

void DrinkableFoodItem::fromJson(const std::string &name, const nlohmann::json &j)
{
    name_ = name;
    meal_ = j.at("meal").get<std::string>();
    calories_ = j.at("calories").get<int>();
    carbs_ = j.at("carbs").get<int>();
    protein_ = j.at("protein").get<int>();
    fat_ = j.at("fat").get<int>();
    type_ = j.at("type").get<std::string>();
    quantityInMilliliters_ = j.at("quantity").get<int>();
}

nlohmann::json DrinkableFoodItem::toJson() const
{
    nlohmann::json baseJson = FoodItem::toJson(); // Get common attributes
    baseJson["quantity"] = quantityInMilliliters_;

    return baseJson;
}