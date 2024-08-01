#include "NutritionServer.hpp"

NutritionServer &NutritionServer::getInstance()
{
    static NutritionServer instance;
    return instance;
}

NutritionServer::NutritionServer()
    : logger_("data/logs/server_log.txt")
{
    // Initialize food Items
    populateFoodItems();

    usersFilePath_ = "data/users.txt";
}

void NutritionServer::receiveUserInfo(const User &user)
{
    users_.push_back(user);
    std::ostringstream oss;
    oss << "Received info for user: " << user.getName();
    logInfo(oss.str());
    saveUserInfo(user);
}

void NutritionServer::generateDietPlan(const User &user)
{
    DietPlan plan;
    plan.createPlan(user, foodItems_);
    // Save or send the plan (stubbed)
    logInfo("Generated diet plan for user: " + user.getName());
    plan.display();
}

void NutritionServer::logInfo(const std::string &info)
{
    logger_.log(info);
}

void NutritionServer::populateFoodItems()
{
    // Path to the food items JSON file
    std::string filePath = "data/food_items.json";

    // Open the file
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    // Parse the JSON file
    nlohmann::json jsonData;
    try
    {
        file >> jsonData;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        return;
    }

    // Iterate through the JSON data and populate food items
    for (auto &item : jsonData.items())
    {
        auto foodJson = item.value();
        try
        {
            std::string name = item.key();
            int calories = foodJson.at("calories").get<int>();
            int carbs = foodJson.at("carbs").get<int>();
            int protein = foodJson.at("protein").get<int>();
            int fat = foodJson.at("fat").get<int>();
            std::string meal = foodJson.at("meal").get<std::string>();
            std::string type = foodJson.at("type").get<std::string>();

            // Create a FoodItem object and add it to the vector
            FoodItem foodItem(name, calories, carbs, protein, fat, meal, type, 1);
            foodItems_.push_back(foodItem);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing food item: " << e.what() << std::endl;
        }
    }

    std::cout << "Food items successfully populated from JSON file." << std::endl;
}

void NutritionServer::analyzeData()
{
    statistics_.analyze(users_);
    statistics_.saveStatistics("data/logs/statistics.txt");
    statistics_.display();
}

void NutritionServer::saveUserInfo(const User &user)
{
    std::ofstream outFile(usersFilePath_, std::ios::app);
    if (outFile.is_open())
    {
        outFile << "Name: " << user.getName() << std::endl
                << "Age: " << user.getAge() << ", Gender: " << user.getGender() << std::endl
                << "Weight:" << user.getWeight() << ", Height: " << user.getHeight() << std::endl
                << std::endl;
        outFile.close();
    }
}