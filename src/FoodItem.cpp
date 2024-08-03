#include "FoodItem.hpp"

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

// Static method to create a FoodItem object from JSON data
FoodItem FoodItem::fromJson(const std::string &name, const nlohmann::json &j)
{
    int calories = j.at("calories").get<int>();
    int carbs = j.at("carbs").get<int>();
    int protein = j.at("protein").get<int>();
    int fat = j.at("fat").get<int>();
    std::string meal = j.at("meal").get<std::string>();
    std::string type = j.at("type").get<std::string>();

    return FoodItem(name, calories, carbs, protein, fat, meal, type);
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
