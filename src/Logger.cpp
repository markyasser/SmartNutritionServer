#include "Logger.hpp"

Logger::Logger(const std::string &logFilePath) : logFilePath_(logFilePath) {}

void Logger::log(const std::string &info)
{
    logToFile(logFilePath_, info);
}

void Logger::logToFile(const std::string &filePath, const std::string &info)
{
    std::ofstream logFile(filePath, std::ios_base::app);
    logFile << info << std::endl;
}
