#pragma once
#include <string>
#include <vector>
#include <set>
#include <json.hpp>

class User
{
public:
    User();
    User(const std::string &name, int age, double weight, double height, const std::string &gender,
         bool isHighBloodPressure, bool isDiabetic, float sedentaryActivityLevel, std::set<std::string> excludedFoods);
    std::string getName() const;
    double getWeight() const;
    double getHeight() const;
    int getAge() const;
    std::string getGender() const;
    int IsHighBloodPressure() const;
    std::set<std::string> getExcludedFoods() const;
    bool IsDiabetic() const;
    float getSedentaryActivityLevel() const;
    void toJson(nlohmann::json &j) const;
    static User fromJson(const nlohmann::json &j);

private:
    // Personal data
    std::string name_;
    int age_;
    std::string gender_;
    std::set<std::string> excludedFoods_;

    // Health data
    double weight_;
    double height_;
    float sedentaryActivityLevel_;

    // Pre-existing conditions
    bool isDiabetic_;
    bool isHighBloodPressure_;
};
