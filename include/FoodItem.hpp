#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>

class FoodItem
{
public:
    FoodItem(const std::string &name, int calories, int carbs, int protein, int fat, const std::string &meal, const std::string &type, int quantity);
    // Getter methods
    std::string getName() const;
    int getCalories() const;
    int getCarbs() const;
    int getProtein() const;
    int getFat() const;
    std::string getMeal() const;
    std::string getType() const;

private:
    std::string name_;
    int calories_;
    int carbs_;
    int protein_;
    int fat_;
    std::string meal_;
    std::string type_;
};