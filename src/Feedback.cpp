#include "Feedback.hpp"

// Definition of static member variable
const std::string Feedback::feedbackFilePath_ = "./data/feedback.json";

// Default constructor
Feedback::Feedback()
{
    totalFeedbacks_ = 0;
    averageRating_ = 0.0;
    feedback_ = 0;
}

// Constructor with initial feedback
Feedback::Feedback(int feedback)
    : feedback_(feedback) {}

// Static method to create a Feedback object from JSON
Feedback Feedback::fromJson(const nlohmann::json &j)
{
    Feedback fb;
    fb.totalFeedbacks_ = j.at("totalFeedbacks").get<int>();
    fb.averageRating_ = j.at("averageRating").get<double>();
    return fb;
}

// Method to convert Feedback object to JSON
nlohmann::json Feedback::toJson() const
{
    return nlohmann::json{
        {"totalFeedbacks", totalFeedbacks_},
        {"averageRating", averageRating_}};
}

// Getter for feedback
int Feedback::getFeedback() const
{
    return feedback_;
}

// Getter for total feedbacks
int Feedback::getTotalFeedbacks() const
{
    return totalFeedbacks_;
}

// Getter for average rating
double Feedback::getAverageRating() const
{
    return averageRating_;
}

// Adds new feedback and updates total feedbacks and average rating
void Feedback::addFeedback(int newFeedback)
{
    feedback_ = newFeedback;
    updateFeedback();
}

// Private helper method to update total feedbacks
void Feedback::updateTotalFeedbacks(int newTotal)
{
    totalFeedbacks_ = newTotal;
}

// Private helper method to update average rating
void Feedback::updateAverageRating(double newAverage)
{
    averageRating_ = newAverage;
}

// Reads feedback data from a file
void Feedback::updateFeedback()
{
    std::ifstream inputFile(feedbackFilePath_);
    if (inputFile.is_open())
    {
        nlohmann::json j;
        inputFile >> j;
        Feedback fb = Feedback::fromJson(j);
        int newTotal = fb.getTotalFeedbacks() + 1;
        double newAverage = (fb.getAverageRating() * fb.getTotalFeedbacks() + feedback_) / newTotal;
        updateTotalFeedbacks(newTotal);
        updateAverageRating(newAverage);
        inputFile.close();
    }
}

// Reads feedback data from a file
Feedback Feedback::readFromFile()
{
    std::ifstream inputFile(feedbackFilePath_);
    if (inputFile.is_open())
    {
        nlohmann::json j;
        inputFile >> j;
        Feedback fb = Feedback::fromJson(j);
        inputFile.close();
        return fb;
    }
    return Feedback();
}

// Writes feedback data to a file
void Feedback::writeToFile() const
{
    std::ofstream outputFile(feedbackFilePath_);
    if (outputFile.is_open())
    {
        nlohmann::json j = toJson();
        outputFile << j.dump(4); // Pretty print with 4-space indentation
        outputFile.close();
    }
}
