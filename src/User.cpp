#include "User.hpp"

User::User(const std::string &name, int age, double weight, double height, const std::string &gender, int bloodPressureUpper, int bloodPressureLower, bool isDiabetic)
{
    name_ = name;
    age_ = age;
    weight_ = weight;
    height_ = height;
    gender_ = gender;
    bloodPressureUpper_ = bloodPressureUpper;
    bloodPressureLower_ = bloodPressureLower;
    isDiabetic_ = isDiabetic;
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
