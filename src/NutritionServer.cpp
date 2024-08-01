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

    usersFilePath_ = "users.json";
}

void NutritionServer::receiveUserInfo(const User &user)
{
    users_.push_back(user);
    std::ostringstream oss;
    oss << "Received info for user: " << user.getName();
    logInfo(oss.str());
    saveUserInfo(user);
}

nlohmann::json NutritionServer::generateDietPlan(const User &user)
{
    DietPlan plan;
    plan.createPlan(user, foodItems_);
    // Save or send the plan (stubbed)
    logInfo("Generated diet plan for user: " + user.getName());
    // plan.display();
    return plan.toJson();
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
            foodItems_.push_back(FoodItem::fromJson(item.key(), foodJson));
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing food item: " << e.what() << std::endl;
        }
    }

    std::cout << "Food items successfully populated from JSON file." << std::endl;
}

nlohmann::json NutritionServer::analyzeData()
{
    // Load users
    std::vector<User> users;
    bool success = JsonManager<User>::readFromFile(usersFilePath_, users);

    statistics_.analyze(users);
    statistics_.saveStatistics("data/logs/statistics.txt");
    return statistics_.toJson();
}

void NutritionServer::saveUserInfo(const User &user)
{
    // Load existing users
    std::vector<User> users;
    bool loadsuccess = JsonManager<User>::readFromFile(usersFilePath_, users);

    // Add the new user
    users.push_back(user);

    // Write the updated user list to file
    bool writesuccess = JsonManager<User>::writeToFile(usersFilePath_, users);
    if (writesuccess)
    {
        logInfo("User info saved successfully.");
    }
    else
    {
        logInfo("Failed to save user info.");
    }
}