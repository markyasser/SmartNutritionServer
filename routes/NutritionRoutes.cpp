#include "NutritionRoutes.hpp"

void NutritionRoutes::setupRoutes(crow::SimpleApp &app, NutritionServer &server)
{
    // Endpoint to register a user and generate a diet plan
    app.route_dynamic("/register-user")
        .methods("POST"_method)([&server](const crow::request &req)
                                {
        try {
            nlohmann::json userData = nlohmann::json::parse(req.body);
            User user = User::fromJson(userData);

            // Register the user and generate a diet plan
            server.receiveUserInfo(user);
            nlohmann::json res = server.generateDietPlan(user);

            return crow::response{200, res.dump()};
        } catch (const nlohmann::json::exception& e) {
            return crow::response{400, "Invalid JSON data"};
        } });

    // Endpoint to analyze data and save statistics
    app.route_dynamic("/analyze-data")
        .methods("GET"_method)([&server]
                               {
            
        // Analyze user data and save statistics
        nlohmann::json res = server.analyzeData();

        return crow::response{200, res.dump()}; });

    // Endpoints to set Feedback from the user to the generated diet plan
    app.route_dynamic("/feedback")
        .methods("POST"_method)([&server](const crow::request &req)
                                {
        try {
            nlohmann::json feedbackData = nlohmann::json::parse(req.body);
            int feedback = feedbackData.at("feedback").get<int>();
            int planId = feedbackData.at("plan_id").get<int>();

            // Log the feedback
            server.logInfo("Feedback: " + feedback);

            return crow::response{200, "Feedback received"};
        } catch (const nlohmann::json::exception& e) {
            return crow::response{400, "Invalid JSON data"};
        } });
}
