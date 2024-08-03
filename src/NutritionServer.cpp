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

bool NutritionServer::receiveFeedback(int feedback)
{
    Feedback feedbackObj;
    feedbackObj.addFeedback(feedback);
    logInfo("Received feedback: " + std::to_string(feedback));
    feedbackObj.writeToFile();
    return true;
}

bool NutritionServer::receiveUserInfo(const User &user)
{
    users_.push_back(user);
    std::ostringstream oss;
    oss << "Received info for user: " << user.getName();
    logInfo(oss.str());
    saveUserInfo(user);
    return true;
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

nlohmann::json NutritionServer::getRating()
{
    Feedback feedbackObj = Feedback::readFromFile();
    return feedbackObj.toJson();
}

nlohmann::json NutritionServer::getFoodItems()
{
    nlohmann::json foodItemsJson;
    foodItemsJson["fooditems"] = nlohmann::json::array();
    for (const auto &item : foodItems_)
    {
        foodItemsJson["fooditems"].push_back(item->toJson()["name"]);
    }
    return foodItemsJson;
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
        std::string name = item.key();
        FoodItem *foodItem;
        try
        {
            std::string quantityType = foodJson.at("quantity_type").get<std::string>();
            if (quantityType == "quantitable")
            {
                foodItem = new QuantitableFoodItem();
                foodItem->fromJson(name, foodJson);
            }
            else if (quantityType == "drinkable")
            {
                foodItem = new DrinkableFoodItem();
                foodItem->fromJson(name, foodJson);
            }
            else if (quantityType == "weightable")
            {
                foodItem = new WeightableFoodItem();
                foodItem->fromJson(name, foodJson);
            }
            else
            {
                throw std::runtime_error("Invalid quantity type: " + quantityType);
            }
            foodItems_.push_back(foodItem);
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

    Statistics statistics_;
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