#include "Logger.hpp"
#include <iostream>
#include <fstream>

void Logger::log(const std::string &info)
{
    std::ofstream logFile("data/logs/server_log.txt", std::ios_base::app);
    logFile << info << std::endl;
    logFile.close();
}
