#pragma once
#include <string>

class User
{
public:
    User(const std::string &name, int age, double weight, double height, const std::string &gender,
         int bloodPressureUpper, int bloodPressureLower, bool isDiabetic);
    std::string getName() const;
    double getWeight() const;
    double getHeight() const;
    int getAge() const;
    std::string getGender() const;
    int getBloodPressureUpper() const;
    int getBloodPressureLower() const;
    bool getIsDiabetic() const;

private:
    // Personal data
    std::string name_;
    int age_;
    std::string gender_;

    // Health data
    double weight_;
    double height_;
    int bloodPressureUpper_;
    int bloodPressureLower_;
    bool isDiabetic_;

    // Diet plan
    int dietPlanId;
};
