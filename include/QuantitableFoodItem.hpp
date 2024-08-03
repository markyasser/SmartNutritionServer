#pragma once
#include "FoodItem.hpp"

class QuantitableFoodItem : public FoodItem
{
public:
    QuantitableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantity);

    int getQuantity() const;

    static QuantitableFoodItem *fromJson(const std::string &name, const nlohmann::json &j);
    nlohmann::json toJson() const;

private:
    int quantity_;
};
