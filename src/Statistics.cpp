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

    for (const auto &user : users)
    {
        averageWeight_ += user.getWeight();
        averageHeight_ += user.getHeight();

        // Update the height histogram with ranges
        int height = user.getHeight();
        std::string heightRange = determineRange(height, 10); // Change 10 to your preferred range size
        heightHistogram_[heightRange]++;

        // Update the weight histogram with ranges
        int weight = user.getWeight();
        std::string weightRange = determineRange(weight, 5); // Change 5 to your preferred range size
        weightHistogram_[weightRange]++;

        // Update the diabetes statistics
        if (user.getGender() == "male" && user.IsDiabetic())
            totalDiabeticMales++;
        else if (user.getGender() == "female" && user.IsDiabetic())
            totalDiabeticFemales++;
        else
            totalNonDiabetic++;
    }

    // Calculate averages
    averageWeight_ /= users.size();
    averageHeight_ /= users.size();
}

std::string Statistics::determineRange(int value, int rangeSize) const
{
    int lowerBound = (value / rangeSize) * rangeSize;
    int upperBound = lowerBound + rangeSize - 1;
    return std::to_string(lowerBound) + "-" + std::to_string(upperBound);
}

void Statistics::saveStatistics(const std::string &filePath) const
{
    std::ofstream outFile(filePath);
    if (outFile.is_open())
    {
        outFile << std::fixed << std::setprecision(2);

        // Save average weight and height
        outFile << "Average Weight: " << averageWeight_ << " kg" << std::endl;
        outFile << "Average Height: " << averageHeight_ << " cm" << std::endl;

        // Save diabetic statistics
        outFile << "Total Diabetic Males: " << totalDiabeticMales << std::endl;
        outFile << "Total Diabetic Females: " << totalDiabeticFemales << std::endl;
        outFile << "Total Non-Diabetic: " << totalNonDiabetic << std::endl;

        // Save histograms
        outFile << "Height Histogram:" << std::endl;
        for (const auto &entry : heightHistogram_)
        {
            outFile << "  " << entry.first << ": " << entry.second << std::endl;
        }

        outFile << "Weight Histogram:" << std::endl;
        for (const auto &entry : weightHistogram_)
        {
            outFile << "  " << entry.first << ": " << entry.second << std::endl;
        }

        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
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
