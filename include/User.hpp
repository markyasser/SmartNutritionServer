#pragma once
#include <string>
#include <json.hpp>

class User
{
public:
    User(const std::string &name, int age, double weight, double height, const std::string &gender,
         int bloodPressureUpper, int bloodPressureLower, bool isDiabetic, std::vector<std::string> excludedFoods);
    std::string getName() const;
    double getWeight() const;
    double getHeight() const;
    int getAge() const;
    std::string getGender() const;
    int getBloodPressureUpper() const;
    int getBloodPressureLower() const;
    std::vector<std::string> getExcludedFoods() const;
    bool getIsDiabetic() const;
    void toJson(nlohmann::json &j) const;
    static User fromJson(const nlohmann::json &j);

private:
    // Personal data
    std::string name_;
    int age_;
    std::string gender_;
    std::vector<std::string> excludedFoods_;

    // Health data
    double weight_;
    double height_;
    int bloodPressureUpper_;
    int bloodPressureLower_;
    bool isDiabetic_;

    // Diet plan
    int dietPlanId;
};
