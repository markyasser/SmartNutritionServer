#pragma once
#include "FoodItem.hpp"

class WeightableFoodItem : public FoodItem
{
public:
    WeightableFoodItem();
    WeightableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInGrams);

    int getQuantity() const;
    void fromJson(const std::string &name, const nlohmann::json &j);
    nlohmann::json toJson() const;

private:
    int quantityInGrams_;
};
