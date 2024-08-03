#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>

class Logger
{
public:
    Logger(const std::string &logFilePath);
    void log(const std::string &info);

private:
    std::string logFilePath_;
    void logToFile(const std::string &filePath, const std::string &info);
    std::string getCurrentTime(); // Declare the new method
};
