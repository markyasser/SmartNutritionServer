#include "NutritionServer.hpp"

NutritionServer &NutritionServer::getInstance()
{
    logger_.log("Initiated NutritionServer");
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
    logger_.log("Received feedback: " + std::to_string(feedback));
    feedbackObj.writeToFile();
    return true;
}

bool NutritionServer::receiveUserInfo(const User &user)
{
    users_.push_back(user);
    std::ostringstream oss;
    oss << "Received info for user: " << user.getName();
    logger_.log(oss.str());
    saveUserInfo(user);
    logger_.log("User " + user.getName() + " info saved successfully.");
    return true;
}

nlohmann::json NutritionServer::generateDietPlan(const User &user)
{
    DietPlan plan;
    plan.createPlan(user, foodItems_);
    logger_.log("Generated diet plan for user: " + user.getName());
    return plan.toJson();
}

nlohmann::json NutritionServer::getRating()
{
    Feedback feedbackObj = Feedback::readFromFile();
    logger_.log("Retrieved feedback rating.");
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
    logger_.log("Retrieved food items.");
    return foodItemsJson;
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
        logger_.log("Failed to open file: " + filePath);
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
        logger_.log("Failed to parse JSON: " + std::string(e.what()));
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
            logger_.log("Error processing food item: " + std::string(e.what()));
            std::cerr << "Error processing food item: " << e.what() << std::endl;
        }
    }

    std::cout << "Food items successfully populated from JSON file." << std::endl;
    logger_.log("Food items successfully populated from JSON file.");
}

nlohmann::json NutritionServer::analyzeData()
{
    // Load users
    std::vector<User> users;
    bool success = JsonManager<User>::readFromFile(usersFilePath_, users);

    Statistics statistics_;
    statistics_.analyze(users);
    statistics_.saveStatistics("data/logs/statistics.txt");
    logger_.log("Data analysis complete.");
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
    JsonManager<User>::writeToFile(usersFilePath_, users);
}