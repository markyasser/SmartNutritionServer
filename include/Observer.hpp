#pragma once
#include <string>

class Observer
{
public:
    virtual void update(const std::string &data) = 0;
};
