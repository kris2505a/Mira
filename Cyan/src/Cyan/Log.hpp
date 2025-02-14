#pragma once
#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace Cyan {

	class CYANAPI Log {
	private:
		static std::shared_ptr <spdlog::logger> coreLogger;
		static std::shared_ptr <spdlog::logger> gameLogger;


	public:
		static void init();
		inline static std::shared_ptr <spdlog::logger>& getCoreLogger(){ return coreLogger; }
		inline static std::shared_ptr <spdlog::logger>& getGameLogger(){ return gameLogger; }

	};
}

#define CY_ERROR error
#define CY_WARN warn
#define CY_INFO info
#define CY_FATAL critical
#define CY_TRACE trace

#define CYAN_LOG(TYPE, ...) ::Cyan::Log::getCoreLogger()->TYPE(__VA_ARGS__)

#define LOG(TYPE, ...) ::Cyan::Log::getGameLogger()->TYPE(__VA_ARGS__)
	


