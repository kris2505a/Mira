#pragma once
#include "Core.hpp"

namespace Mira 
{

class MIRA_API Game {
public:
	virtual auto update() -> void = 0;
	Game() = default;
	virtual ~Game() = default;
};

}