#pragma once
#include <chrono>
#include <string>

#include <Core.h>
#include <ctime>

enum class LogType {
	MESSAGE,
	DEBUG,
	ERROR,
	CRITICAL
};

class API Log {
private:
	std::time_t m_currentTime;
	std::tm* m_localTime;

public:
	Log() = default;
	~Log() = default;
	void engineLog(LogType type, const std::string& logMessage);

};

