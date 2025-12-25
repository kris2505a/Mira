#pragma once
#include <chrono>
#include "Core/Core.hpp"

namespace Mira {

class MIRA_API Timer {
public:
	Timer();
	~Timer() = default;
	float elapsed();

private:
	std::chrono::high_resolution_clock::time_point m_currentTime;
	std::chrono::high_resolution_clock::time_point m_previousTime;
};

}