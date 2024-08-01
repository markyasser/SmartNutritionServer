#include <json.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

template <typename T>
class JsonManager
{
    static const std::string folderPath;

public:
    // Read data from a JSON file
    static bool readFromFile(const std::string &filePath, std::vector<T> &data);

    // Write data to a JSON file
    static bool writeToFile(const std::string &filePath, const std::vector<T> &data);
};

// Define the static member
template <typename T>
const std::string JsonManager<T>::folderPath = "data/";

// Implementation of static methods

template <typename T>
bool JsonManager<T>::readFromFile(const std::string &filePath, std::vector<T> &data)
{
    using json = nlohmann::json;

    std::ifstream inFile(folderPath + filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Failed to open file: " << folderPath + filePath << std::endl;
        return false;
    }

    json jsonData;
    try
    {
        inFile >> jsonData;
        if (!jsonData.is_array())
        {
            std::cerr << "Expected JSON array" << std::endl;
            return false;
        }

        data.clear();
        for (const auto &item : jsonData)
        {
            data.push_back(T::fromJson(item));
        }
    }
    catch (const json::exception &e)
    {
        std::cerr << "Error reading JSON data: " << e.what() << std::endl;
        return false;
    }
    return true;
}

template <typename T>
bool JsonManager<T>::writeToFile(const std::string &filePath, const std::vector<T> &data)
{
    using json = nlohmann::json;

    json jsonData = json::array();
    for (const auto &item : data)
    {
        json itemJson;
        item.toJson(itemJson);
        jsonData.push_back(itemJson);
    }

    std::ofstream outFile(folderPath + filePath);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open file: " << folderPath + filePath << std::endl;
        return false;
    }

    try
    {
        outFile << jsonData.dump(4) << std::endl; // Pretty print with 4 spaces
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error writing JSON data: " << e.what() << std::endl;
        return false;
    }
    return true;
}
