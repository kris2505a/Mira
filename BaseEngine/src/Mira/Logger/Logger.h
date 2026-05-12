#pragma once
#include <format>
#include <string>

#include "Mira/Core/Core.h"

namespace Mira {

enum class MIRA_API LogType : int {
    Info,
    Debug,
    Warning,
    Error
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
        project = "Engine";
#elif MIRA_GAME
        project = "Game";
#endif

        auto msg = std::format(
            logStr,
            std::forward<Args>(args)...
        );

        logMessage(msg, project, type);
    }

private:
    static void logMessage(
        const std::string& str,
        const std::string& logProject,
        LogType type
    );

    static std::string getTimeNow();

    static const char* typeToString(LogType type);

    static const char* getColor(LogType type);
};

}