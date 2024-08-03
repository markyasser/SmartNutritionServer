#include "WeightableFoodItem.hpp"

WeightableFoodItem::WeightableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInGrams)
    : FoodItem(name, calories, carbs, protein, fat, meal, type), quantityInGrams_(quantityInGrams)
{
}

int WeightableFoodItem::getQuantityInGrams() const
{
    return quantityInGrams_;
}

WeightableFoodItem *WeightableFoodItem::fromJson(const std::string &name, const nlohmann::json &j)
{
    FoodItem base = FoodItem::fromJson(name, j); // Extract common attributes
    int quantityInGrams = j.at("quantity").get<int>();

    return new WeightableFoodItem(base.getName(), base.getCalories(), base.getCarbs(), base.getProtein(), base.getFat(), base.getMeal(), base.getType(), quantityInGrams);
}

nlohmann::json WeightableFoodItem::toJson() const
{
    nlohmann::json baseJson = FoodItem::toJson(); // Get common attributes
    baseJson["quantity"] = quantityInGrams_;

    return baseJson;
}