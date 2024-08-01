#include "NutritionRoutes.hpp"

void NutritionRoutes::setupRoutes(Crow::SimpleApp &app, NutritionServer &server)
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
            server.generateDietPlan(user);

            return crow::response{200, "User registered and diet plan generated"};
        } catch (const nlohmann::json::exception& e) {
            return crow::response{400, "Invalid JSON data"};
        } });

    // Endpoint to analyze data and save statistics
    app.route_dynamic("/analyze-data")
        .methods("GET"_method)([&server]
                               {
        // Analyze user data and save statistics
        server.analyzeData();

        return crow::response{200, "Data analyzed and statistics saved"}; });
}
