#include "Logger.hpp"

Logger::Logger(const std::string &logFilePath) : logFilePath_(logFilePath) {}

void Logger::log(const std::string &info)
{
    std::string timeStampedInfo = getCurrentTime() + " " + info;
    logToFile(logFilePath_, timeStampedInfo);
}

void Logger::logToFile(const std::string &filePath, const std::string &info)
{
    std::ofstream logFile(filePath, std::ios_base::app);
    if (logFile.is_open())
    {
        logFile << info << std::endl;
    }
    else
    {
        std::cerr << "Unable to open log file: " << filePath << std::endl;
    }
}

std::string Logger::getCurrentTime()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto now_c = system_clock::to_time_t(now);
    std::tm now_tm;

#ifdef _WIN32
    localtime_s(&now_tm, &now_c);
#else
    localtime_r(&now_c, &now_tm);
#endif

    std::ostringstream oss;
    oss << "[" << std::put_time(&now_tm, "%H:%M:%S") << "]";
    return oss.str();
}