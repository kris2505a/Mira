#pragma once
#include "Mira/Core/Core.hpp"

#include <chrono>

namespace Mira {

class MIRA_API Clock {
public:
	
	static float getTime() {
		auto now = std::chrono::steady_clock::now();

		return std::chrono::duration<double>(now.time_since_epoch()).count();
	}


};

}