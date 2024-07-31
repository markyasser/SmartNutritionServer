#include "User.hpp"

User::User(const std::string &name, int age, double weight, double height)
    : name_(name), age_(age), weight_(weight), height_(height) {}

std::string User::getName() const
{
    return name_;
}
