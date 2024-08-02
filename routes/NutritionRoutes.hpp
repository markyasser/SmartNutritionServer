#pragma once
#include <crow.h>
#include "NutritionServer.hpp" // Include your NutritionServer header
#include <vector>
#include <json.hpp>
#include "Cors.hpp"

class NutritionRoutes
{
public:
    static void setupRoutes(crow::App<Cors> &app, NutritionServer &server);
};
