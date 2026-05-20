#include "MiraPch.hpp"
#include "Logger.hpp"


namespace Mira {

void Logger::logMessage(
    const std::string& str,
    const std::string& logProject,
    LogType type
)
{
    std::cout
        << "["
        << getTimeNow()
        << "]["
        << logProject
        << "]["
        << getColor(type)
        << typeToString(type)
        << "\033[0m"
        << "] "
        << str
        << "\n";
}

std::string Logger::getTimeNow() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};
    localtime_s(&localTime, &time);

    std::ostringstream oss;

    oss << std::put_time(&localTime, "%H:%M:%S");
    return oss.str();
}

const char* Logger::typeToString(LogType type) {
    switch (type) {
    case LogType::Info:
        return "Info";

    case LogType::Error:
        return "Error";

    case LogType::Warning:
        return "Warning";

    case LogType::Debug:
        return "Debug";
    }

    return "Unknown";
}

const char* Logger::getColor(LogType type) {
    switch (type) {
    case LogType::Info:
        return "\033[32m";

    case LogType::Debug:
        return "\033[36m";

    case LogType::Warning:
        return "\033[33m";

    case LogType::Error:
        return "\033[31m";
    }

    return "\033[0m";
}

}