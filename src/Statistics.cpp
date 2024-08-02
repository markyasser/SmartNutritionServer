#include "Statistics.hpp"
#include <fstream>
#include <numeric>
#include <iomanip>
#include <iostream>

void Statistics::analyze(const std::vector<User> &users)
{
    calculateStatistics(users);
}

void Statistics::calculateStatistics(const std::vector<User> &users)
{
    if (users.empty())
    {
        averageWeight_ = 0.0;
        averageHeight_ = 0.0;
        return;
    }
    int totalMen = 0;
    int totalDiabeticMen = 0;
    for (auto user : users)
    {
        averageWeight_ += user.getWeight();
        averageHeight_ += user.getHeight();

        // Update the height histogram
        int height = user.getHeight();
        if (heightHistogram_.find(height) == heightHistogram_.end())
            heightHistogram_[height] = 1;
        else
            heightHistogram_[height]++;

        // Update the weight histogram
        int weight = user.getWeight();
        if (weightHistogram_.find(weight) == weightHistogram_.end())
            weightHistogram_[weight] = 1;
        else
            weightHistogram_[weight]++;

        // Update the percentage of
        if (user.getGender() == "male" && user.getIsDiabetic())
            totalDiabeticMales++;

        else if (user.getGender() == "female" && user.getIsDiabetic())
            totalDiabeticFemales++;

        else
            totalNonDiabetic++;
    }
}
void Statistics::saveStatistics(const std::string &filePath) const
{
    std::ofstream outFile(filePath);
    if (outFile.is_open())
    {
        outFile << std::fixed << std::setprecision(2);
        outFile << "Average Weight: " << averageWeight_ << " kg" << std::endl;
        outFile << "Average Height: " << averageHeight_ << " cm" << std::endl;
        outFile.close();
    }
}

void Statistics::display() const
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Weight: " << averageWeight_ << " kg" << std::endl;
    std::cout << "Average Height: " << averageHeight_ << " cm" << std::endl;
}

nlohmann::json Statistics::toJson() const
{
    nlohmann::json j;
    j["averageWeight"] = averageWeight_;
    j["averageHeight"] = averageHeight_;
    j["diabeticMales"] = totalDiabeticMales;
    j["diabeticFemales"] = totalDiabeticFemales;
    j["nonDiabetic"] = totalNonDiabetic;
    j["heightHistogram"] = heightHistogram_;
    j["weightHistogram"] = weightHistogram_;
    return j;
}
