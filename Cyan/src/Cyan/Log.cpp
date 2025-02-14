#include "PreCompHeaders.hpp"
#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Cyan::Log::coreLogger;
std::shared_ptr<spdlog::logger> Cyan::Log::gameLogger;

namespace Cyan {

		
	void Log::init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("CYAN");
		coreLogger->set_level(spdlog::level::trace);
		gameLogger = spdlog::stdout_color_mt("GAME");
		gameLogger->set_level(spdlog::level::trace);
	}
}