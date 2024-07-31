#pragma once
#include <string>
#include <fstream>

class Logger
{
public:
    Logger(const std::string &logFilePath);
    void log(const std::string &info);
    void logToFile(const std::string &filePath, const std::string &info);

private:
    std::string logFilePath_;
};
