#pragma once
#include <string>

class User
{
public:
    User(const std::string &name, int age, double weight, double height);
    std::string getName() const;

private:
    std::string name_;
    int age_;
    double weight_;
    double height_;
};
