#include "WeightableFoodItem.hpp"

WeightableFoodItem::WeightableFoodItem() : FoodItem()
{
}

WeightableFoodItem::WeightableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInGrams)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantityInGrams_(quantityInGrams)
{
}

int WeightableFoodItem::getQuantity() const
{
    return quantityInGrams_;
}

void WeightableFoodItem::fromJson(const std::string &name, const nlohmann::json &j)
{
    name_ = name;
    meal_ = j.at("meal").get<std::string>();
    calories_ = j.at("calories").get<int>();
    carbs_ = j.at("carbs").get<int>();
    protein_ = j.at("protein").get<int>();
    fat_ = j.at("fat").get<int>();
    type_ = j.at("type").get<std::string>();
    quantityInGrams_ = j.at("quantity").get<int>();
}

nlohmann::json WeightableFoodItem::toJson() const
{
    nlohmann::json baseJson = FoodItem::toJson(); // Get common attributes
    baseJson["quantity"] = std::to_string(quantityInGrams_) + " grams";

    return baseJson;
}