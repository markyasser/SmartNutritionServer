#include "NutritionRoutes.hpp"

void NutritionRoutes::setupRoutes(crow::App<Cors> &app, NutritionServer &server)
{
    // Endpoint to analyze data and save statistics
    CROW_ROUTE(app, "/dashboard").methods("GET"_method)([&server]
                                                        {
        crow::response res;
        
        // Analyze user data and save statistics
        nlohmann::json responseJson;
        responseJson["statistics"] = server.analyzeData();
        responseJson["rating"] = server.getRating();
        res.body = responseJson.dump();
        res.code = 200;

        return res; });
    // Endpoint to get food items
    CROW_ROUTE(app, "/food-items").methods("GET"_method)([&server]
                                                         {
        crow::response res;
        res.body = server.getFoodItems().dump();
        res.code = 200;

        return res; });

    // Endpoint to register a user and generate a diet plan
    CROW_ROUTE(app, "/register-user").methods("POST"_method)([&server](const crow::request &req)
                                                             {
        try {
            crow::response res;
            std::cout << req.url << std::endl;
            nlohmann::json userData = nlohmann::json::parse(req.body);
            User user = User::fromJson(userData);
            
            // Register the user and generate a diet plan
            server.receiveUserInfo(user);
            nlohmann::json dietPlan = server.generateDietPlan(user);
            res.body = dietPlan.dump();
            res.code = 200;
            return res;
        } catch (const nlohmann::json::exception& e) {
            return crow::response{400, "Invalid JSON data"};
        } });

    // Endpoints to set Feedback from the user to the generated diet plan
    CROW_ROUTE(app, "/feedback").methods("POST"_method)([&server](const crow::request &req)
                                                        {
        try {
            crow::response res;

            nlohmann::json feedbackData = nlohmann::json::parse(req.body);
            int feedback = feedbackData.at("feedback").get<int>();

            // Receive feedback from the user
            bool status = server.receiveFeedback(feedback);

            nlohmann::json responseJson;
            if (!status) {
                responseJson["status"] = "error";
                responseJson["message"] = "Failed to receive feedback";
                res.code = 500;
            }
            else {
                responseJson["status"] = "success";
                responseJson["message"] = "Feedback received";
                res.code = 200;
            }
            res.body = responseJson.dump();
            return res;

        } catch (const nlohmann::json::exception& e) {
            return crow::response{400, "Invalid JSON data"};
        } });
}
