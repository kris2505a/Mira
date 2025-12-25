#include <PreCompHeader.hpp>
#include "Log.hpp"


std::time_t Log::m_now = std::time(nullptr);
std::tm Log::m_localTime = {};
std::string Log::m_logColors[] = {
									"\033[37m",			//white 
									"\033[33m",			//yellow
									"\033[38;5;208m",	//orange
									"\033[31m",			//red
									"\033[0m"			//reset
								 };

static std::ofstream g_logFile;

void Log::init() {
	g_logFile.open("Logs/Engine.log", std::ios::out | std::ios::trunc);
}

void Log::shutdown() {
	g_logFile.close();
}

void Log::logTime() {
	m_now = std::time(nullptr);
	localtime_s(&m_localTime, &m_now);
	std::cout << "[" << std::put_time(&m_localTime, "%H:%M:%S") << "]: ";
	g_logFile << "[" << std::put_time(&m_localTime, "%H:%M:%S") << "]: ";
}

void Log::logMessage(int type, const std::string& message) {
	std::cout << m_logColors[type];
	logTime();
	std::cout << "Game ->> " << message << m_logColors[4] << std::endl;
	g_logFile << "Game ->> " << message << std::endl;
}

void Log::logEngineMessage(int type, const std::string& message) {
	std::cout << m_logColors[type];
	logTime();
	std::cout << "Engine ->> " << message << m_logColors[4] << std::endl;
	g_logFile << "Engine ->> " << message << std::endl;
}