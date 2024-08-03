#include "QuantitableFoodItem.hpp"

QuantitableFoodItem::QuantitableFoodItem() : FoodItem()
{
}

QuantitableFoodItem::QuantitableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantity)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantity_(quantity)
{
}

int QuantitableFoodItem::getQuantity() const
{
    return quantity_;
}

void QuantitableFoodItem::fromJson(const std::string &name, const nlohmann::json &j)
{
    name_ = name;
    meal_ = j.at("meal").get<std::string>();
    calories_ = j.at("calories").get<int>();
    carbs_ = j.at("carbs").get<int>();
    protein_ = j.at("protein").get<int>();
    fat_ = j.at("fat").get<int>();
    type_ = j.at("type").get<std::string>();
    quantity_ = j.at("quantity").get<int>();
}

nlohmann::json QuantitableFoodItem::toJson() const
{
    nlohmann::json baseJson = FoodItem::toJson(); // Get common attributes
    baseJson["quantity"] = quantity_;

    return baseJson;
}