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
    std::map<std::string, int> heightHistogram_;
    std::map<std::string, int> weightHistogram_;
    int totalDiabeticMales = 0;
    int totalDiabeticFemales = 0;
    int totalNonDiabetic = 0;

    void calculateStatistics(const std::vector<User> &users);
    std::string determineRange(int value, int rangeSize) const;
};
