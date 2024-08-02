#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <json.hpp>

class Feedback
{
public:
    Feedback();
    Feedback(int feedback);

    // JSON serialization and deserialization
    static Feedback fromJson(const nlohmann::json &j);
    nlohmann::json toJson() const;

    // Getter methods
    int getFeedback() const;
    int getTotalFeedbacks() const;
    double getAverageRating() const;

    // Methods to update feedback data
    void addFeedback(int newFeedback);
    void calculateAverageRating();

    // File I/O methods
    void readFromFile();
    void writeToFile() const;

private:
    // Member variables
    const std::string feedbackFilePath_ = "./data/feedback.json";
    int totalFeedbacks_;
    double averageRating_;
    int feedback_; // Last received feedback

    // Private helper methods
    void updateTotalFeedbacks(int newTotal);
    void updateAverageRating(double newAverage);
};
