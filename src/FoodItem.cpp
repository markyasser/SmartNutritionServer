#include "FoodItem.hpp"

FoodItem::FoodItem() : name_(""), calories_(0), carbs_(0), protein_(0), fat_(0), meal_(""), type_("") {}

FoodItem::FoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type)
    : name_(name), calories_(calories), carbs_(carbs), protein_(protein), fat_(fat), meal_(meal), type_(type) {}

bool FoodItem::operator==(const FoodItem &other) const
{
    return name_ == other.getName() && calories_ == other.getCalories() && carbs_ == other.getCarbs() && protein_ == other.getProtein() && fat_ == other.getFat() && meal_ == other.getMeal() && type_ == other.getType();
}
// Implementing the less-than operator
bool FoodItem::operator<(const FoodItem &other) const
{
    // Example comparison: compare based on `name_` and `calories_` as a tie-breaker
    if (name_ != other.name_)
    {
        return name_ < other.name_;
    }
    return calories_ < other.calories_;
}

nlohmann::json FoodItem::toJson() const
{
    return {
        {"name", name_},
        {"calories", calories_},
        {"carbs", carbs_},
        {"protein", protein_},
        {"fat", fat_},
        {"meal", meal_},
        {"type", type_}};
}

// Getter methods
std::string FoodItem::getName() const { return name_; }
int FoodItem::getCalories() const { return calories_; }
int FoodItem::getCarbs() const { return carbs_; }
int FoodItem::getProtein() const { return protein_; }
int FoodItem::getFat() const { return fat_; }
std::string FoodItem::getMeal() const { return meal_; }
std::string FoodItem::getType() const { return type_; }
