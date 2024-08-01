#include "FoodItem.hpp"

FoodItem::FoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantity)
    : name_(name), calories_(calories), carbs_(carbs), protein_(protein), fat_(fat), meal_(meal), type_(type) {}

// Static method to create a FoodItem object from JSON data
FoodItem FoodItem::fromJson(const std::string &name, const nlohmann::json &j)
{
    int calories = j.at("calories").get<int>();
    int carbs = j.at("carbs").get<int>();
    int protein = j.at("protein").get<int>();
    int fat = j.at("fat").get<int>();
    std::string meal = j.at("meal").get<std::string>();
    std::string type = j.at("type").get<std::string>();

    return FoodItem(name, calories, carbs, protein, fat, meal, type, 1);
}

// Getter methods
std::string FoodItem::getName() const { return name_; }
int FoodItem::getCalories() const { return calories_; }
int FoodItem::getCarbs() const { return carbs_; }
int FoodItem::getProtein() const { return protein_; }
int FoodItem::getFat() const { return fat_; }
std::string FoodItem::getMeal() const { return meal_; }
std::string FoodItem::getType() const { return type_; }
