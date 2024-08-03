#include "User.hpp"

User::User()
{
    name_ = "";
    age_ = 0;
    weight_ = 0;
    height_ = 0;
    isDiabetic_ = false;
    isHighBloodPressure_ = false;
    sedentaryActivityLevel_ = 1.2;
}

User::User(const std::string &name, int age, double weight, double height, const std::string &gender, bool isHighBloodPressure, bool isDiabetic, float sedentaryActivityLevel = 1.2, std::set<std::string> excludedFoods = {})
{
    name_ = name;
    age_ = age;
    weight_ = weight;
    height_ = height;
    gender_ = gender;
    isDiabetic_ = isDiabetic;
    sedentaryActivityLevel_ = sedentaryActivityLevel;
    isHighBloodPressure_ = isHighBloodPressure;
    excludedFoods_ = excludedFoods;
}

std::string User::getName() const
{
    return name_;
}

double User::getWeight() const
{
    return weight_;
}

double User::getHeight() const
{
    return height_;
}

int User::getAge() const
{
    return age_;
}

std::string User::getGender() const
{
    return gender_;
}

int User::IsHighBloodPressure() const
{
    return isHighBloodPressure_;
}

bool User::IsDiabetic() const
{
    return isDiabetic_;
}
float User::getSedentaryActivityLevel() const
{
    return sedentaryActivityLevel_;
}
std::set<std::string> User::getExcludedFoods() const
{
    return excludedFoods_;
}
void User::toJson(nlohmann::json &j) const
{
    j = nlohmann::json{
        {"name", name_},
        {"age", age_},
        {"gender", gender_},
        {"weight", weight_},
        {"height", height_},
        {"is_diabetic", isDiabetic_},
        {"is_high_blood_pressure", isHighBloodPressure_},
        {"sedentary_activity_level", sedentaryActivityLevel_},
        {"excludedFoods", excludedFoods_}};
}

User User::fromJson(const nlohmann::json &j)
{
    return User(j.at("name").get<std::string>(),
                j.at("age").get<int>(),
                j.at("weight").get<double>(),
                j.at("height").get<double>(),
                j.at("gender").get<std::string>(),
                j.at("is_high_blood_pressure").get<int>(),
                j.at("is_diabetic").get<bool>(),
                j.at("sedentary_activity_level").get<float>(),
                j.at("excludedFoods").get<std::set<std::string>>());
}
