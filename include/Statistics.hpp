#pragma once
#include "User.hpp"
#include <vector>
#include <string>

class Statistics
{
public:
    void analyze(const std::vector<User> &users);
    void saveStatistics(const std::string &filePath) const;
    void display() const;
    nlohmann::json toJson() const;

private:
    double averageWeight_ = 0.0;
    double averageHeight_ = 0.0;
    std::map<int, int> heightHistogram_;
    std::map<int, int> weightHistogram_;
    double maleDiabeticRatio = 0.0;
    double femaleDiabeticRatio = 0.0;

    void calculateStatistics(const std::vector<User> &users);
};
