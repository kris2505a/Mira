#include "Log.h"
#include <iostream>

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_ORANGE  "\033[38;5;208m"  // Approximate orange using 256-color
#define COLOR_RED     "\033[31m"

void Log::engineLog(LogType type, const std::string& logMessage) {
	m_currentTime = std::time(nullptr);
	m_localTime = std::localtime(&m_currentTime);
	std::cout << std::put_time(m_localTime, "[%H:%M:%S]: ") << logMessage << std::endl;
}

