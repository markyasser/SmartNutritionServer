#pragma once
#include "FoodItem.hpp"

class DrickableFoodItem : public FoodItem
{
public:
    DrickableFoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantityInMilliliters);

    int getQuantityInMilliliters() const;
    static DrickableFoodItem *fromJson(const std::string &name, const nlohmann::json &j);
    nlohmann::json toJson() const;

private:
    int quantityInMilliliters_;
};
