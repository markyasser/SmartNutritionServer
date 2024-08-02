#include "NutritionRoutes.hpp"

// Helper function to create a JSON response for errors
crow::response createErrorResponse(int code, const std::string &message)
{
    nlohmann::json responseJson;
    responseJson["status"] = "error";
    responseJson["message"] = message;
    return crow::response{code, responseJson.dump()};
}

void NutritionRoutes::setupRoutes(crow::App<Cors> &app, NutritionServer &server)
{
    // Endpoint to analyze data and save statistics
    CROW_ROUTE(app, "/dashboard").methods("GET"_method)([&server]
                                                        {
        try {
            nlohmann::json responseJson;
            responseJson["statistics"] = server.analyzeData();
            responseJson["rating"] = server.getRating();
            crow::response res{200, responseJson.dump()};
            return res;
        } catch (const std::exception& e) {
            return createErrorResponse(500, "Failed to retrieve dashboard data");
        } });

    // Endpoint to get food items
    CROW_ROUTE(app, "/food-items").methods("GET"_method)([&server]
                                                         {
        try {
            nlohmann::json responseJson;
            crow::response res{200, server.getFoodItems().dump()};
            return res;
        } catch (const std::exception& e) {
            return createErrorResponse(500, "Failed to retrieve food items");
        } });

    // Endpoint to register a user and generate a diet plan
    CROW_ROUTE(app, "/register-user").methods("POST"_method)([&server](const crow::request &req)
                                                             {
        try {
            nlohmann::json userData = nlohmann::json::parse(req.body);
            if (!userData.contains("name") || !userData.contains("age") || !userData.contains("weight")) {
                throw std::invalid_argument("Missing required fields");
            }

            User user = User::fromJson(userData);
            server.receiveUserInfo(user);
            nlohmann::json dietPlan = server.generateDietPlan(user);

            crow::response res{200, dietPlan.dump()};
            return res;
        } catch (const nlohmann::json::exception& e) {
            return createErrorResponse(400, "Invalid JSON data");
        } catch (const std::invalid_argument& e) {
            return createErrorResponse(400, e.what());
        } catch (const std::exception& e) {
            return createErrorResponse(500, "Failed to process user registration");
        } });

    // Endpoint to set Feedback from the user to the generated diet plan
    CROW_ROUTE(app, "/feedback").methods("POST"_method)([&server](const crow::request &req)
                                                        {
        try {
            nlohmann::json feedbackData = nlohmann::json::parse(req.body);
            if (!feedbackData.contains("feedback")) {
                throw std::invalid_argument("Missing feedback field");
            }

            int feedback = feedbackData.at("feedback").get<int>();
            bool status = server.receiveFeedback(feedback);

            nlohmann::json responseJson;
            responseJson["status"] = "success";
            responseJson["message"] = "Feedback received";
            crow::response res{200, responseJson.dump()};
            return res;
        } catch (const nlohmann::json::exception& e) {
            return createErrorResponse(400, "Invalid JSON data");
        } catch (const std::invalid_argument& e) {
            return createErrorResponse(400, e.what());
        } catch (const std::exception& e) {
            return createErrorResponse(500, "Failed to process feedback");
        } });
}
