#pragma once
#include <Core/Core.hpp>
#include <chrono>
#include <string>
#include <fstream>


#ifdef API_ENGINE
#define MIRA_LOG(TYPE, ... ) Log::logEngineMessage(TYPE, std::format(__VA_ARGS__))
#else
#define MIRA_LOG(TYPE, ... ) Log::logMessage(TYPE, std::format(__VA_ARGS__))
#endif


#define LOG_INFO 0
#define LOG_DEBUG 1
#define LOG_WARN 2
#define LOG_ERROR 3


class Log {

public:
	Log() = delete;
	~Log() = delete;
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;


	static MIRA_API void logTime();
	static MIRA_API void logMessage(int type, const std::string& message);
	static MIRA_API void logEngineMessage(int type, const std::string& message);


private:
	static std::time_t m_now;
	static std::tm m_localTime;
	static std::string m_logColors[5];
};