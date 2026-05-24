#pragma once
#include <format>
#include <string>
#include <vector>

#include "Mira/Core/Core.hpp"

namespace Mira {

enum class LogType : int {
    Info,
    Debug,
    Warning,
    Error
};

struct LogData {
    std::string time;
    std::string project;
    std::string message;
    LogType type;
};

class MIRA_API Logger {
public:
    Logger() = delete;
    ~Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

public:
    template <typename... Args>
    static void log(
        LogType type,
        std::format_string<Args...> logStr,
        Args&&... args
    )
    {
        std::string project = "Unknown";

#ifdef MIRA_ENGINE
        project = "Mira";
#elif MIRA_GAME
        project = s_gameName;
#endif

        auto msg = std::format(
            logStr,
            std::forward<Args>(args)...
        );

        logMessage(msg, project, type);
    }


    static std::vector<LogData>& getLogData();

private:
    static void logMessage(
        const std::string& str,
        const std::string& logProject,
        LogType type
    );

    static void addLogCache(const LogData& data);

    static std::string getTimeNow();
    static const char* typeToString(LogType type);
    static const char* getColor(LogType type);
    static std::vector<LogData> s_frameLogs;
    static std::string s_gameName;

};

}