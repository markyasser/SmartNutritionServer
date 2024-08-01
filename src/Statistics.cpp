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
    averageWeight_ = std::accumulate(users.begin(), users.end(), 0.0,
                                     [](double sum, const User &user)
                                     { return sum + user.getWeight(); }) /
                     users.size();

    averageHeight_ = std::accumulate(users.begin(), users.end(), 0.0,
                                     [](double sum, const User &user)
                                     { return sum + user.getHeight(); }) /
                     users.size();
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