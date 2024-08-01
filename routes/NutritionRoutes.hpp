#pragma once
#include <crow.h>
#include "NutritionServer.hpp" // Include your NutritionServer header
#include <vector>
#include <json.hpp>

class NutritionRoutes
{
public:
    static void setupRoutes(Crow::SimpleApp &app, NutritionServer &server);
};
