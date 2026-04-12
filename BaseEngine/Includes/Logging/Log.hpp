#pragma once
#include <chrono>
#include <format>
#include <string_view>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Mira {

std::string g_errorType[] = {
	"Info",
	"Warning",
	"Error"
};

enum class LogType : int {
	Info,
	Warning,
	Error
};

class Logger {
public:
	template <typename... Args>
	static void Log(
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
	static void logMessage(const std::string& str, const std::string& logProject, LogType type) {
		std::cout
			<< "[" << getTimeNow() << "] ["
			<< logProject << "] ["
			<< g_errorType[static_cast <int>(type)] << "] >> "
			<< str << "\n";
	}

	static std::string getTimeNow() {
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);

		std::tm localTime{};
		localtime_s(&localTime, &time);

		std::ostringstream oss;

		oss << std::put_time(&localTime, "%H:%M:%S");
		return oss.str();
	}

};

}