#include "User.hpp"

User::User()
{
    name_ = "";
    age_ = 0;
    weight_ = 0;
    height_ = 0;
    bloodPressureLower_ = 0;
    bloodPressureUpper_ = 0;
    isDiabetic_ = false;
}

User::User(const std::string &name, int age, double weight, double height, const std::string &gender, int bloodPressureUpper, int bloodPressureLower, bool isDiabetic, std::set<std::string> excludedFoods = {})
{
    name_ = name;
    age_ = age;
    weight_ = weight;
    height_ = height;
    gender_ = gender;
    bloodPressureUpper_ = bloodPressureUpper;
    bloodPressureLower_ = bloodPressureLower;
    isDiabetic_ = isDiabetic;
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

int User::getBloodPressureUpper() const
{
    return bloodPressureUpper_;
}

int User::getBloodPressureLower() const
{
    return bloodPressureLower_;
}

bool User::getIsDiabetic() const
{
    return isDiabetic_;
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
        {"blood_pressure_upper", bloodPressureUpper_},
        {"blood_pressure_lower", bloodPressureLower_},
        {"excludedFoods", excludedFoods_}};
}

User User::fromJson(const nlohmann::json &j)
{
    return User(j.at("name").get<std::string>(),
                j.at("age").get<int>(),
                j.at("weight").get<double>(),
                j.at("height").get<double>(),
                j.at("gender").get<std::string>(),
                j.at("blood_pressure_upper").get<int>(),
                j.at("blood_pressure_lower").get<int>(),
                j.at("is_diabetic").get<bool>(),
                j.at("excludedFoods").get<std::set<std::string>>());
}
