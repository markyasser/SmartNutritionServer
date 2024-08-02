#pragma once
#include <string>
#include <vector>
#include <set>
#include <json.hpp>

class User
{
public:
    User(const std::string &name, int age, double weight, double height, const std::string &gender,
         int bloodPressureUpper, int bloodPressureLower, bool isDiabetic, std::set<std::string> excludedFoods);
    std::string getName() const;
    double getWeight() const;
    double getHeight() const;
    int getAge() const;
    std::string getGender() const;
    int getBloodPressureUpper() const;
    int getBloodPressureLower() const;
    std::set<std::string> getExcludedFoods() const;
    bool getIsDiabetic() const;
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
    int bloodPressureUpper_;
    int bloodPressureLower_;
    bool isDiabetic_;

    // Diet plan
    int dietPlanId;
};
