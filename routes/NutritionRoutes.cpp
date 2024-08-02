#include "NutritionRoutes.hpp"

void NutritionRoutes::setupRoutes(crow::App<Cors> &app, NutritionServer &server)
{
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

    // Endpoint to analyze data and save statistics
    CROW_ROUTE(app, "/analyze-data").methods("GET"_method)([&server]
                                                           {
        crow::response res;
        
        // Analyze user data and save statistics
        nlohmann::json statistics = server.analyzeData();
        res.body = statistics.dump();
        res.code = 200;

        return res; });

    // Endpoints to set Feedback from the user to the generated diet plan
    CROW_ROUTE(app, "/feedback").methods("POST"_method)([&server](const crow::request &req)
                                                        {
        try {
            crow::response res;

            nlohmann::json feedbackData = nlohmann::json::parse(req.body);
            int feedback = feedbackData.at("feedback").get<int>();
            int planId = feedbackData.at("plan_id").get<int>();

            // Log the feedback
            server.logInfo("Feedback: " + feedback);
            nlohmann::json responseJson;
            responseJson["status"] = "success";
            responseJson["message"] = "Feedback received";
            res.code = 200;
            res.body = responseJson.dump();

            return res;
        } catch (const nlohmann::json::exception& e) {
            return crow::response{400, "Invalid JSON data"};
        } });
}
