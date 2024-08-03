#pragma once
#include "FoodItem.hpp"

class DrinkableFoodItem : public FoodItem
{
public:
    DrinkableFoodItem();
    DrinkableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInMilliliters);

    int getQuantity() const;
    void fromJson(const std::string &name, const nlohmann::json &j);
    nlohmann::json toJson() const;

private:
    int quantityInMilliliters_;
};
