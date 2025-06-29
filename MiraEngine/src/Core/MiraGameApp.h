#pragma once

#include "MiraCore.h"
#include <Events/Event.h>

namespace Mira {
class MIRA_API GameApp {
public:
	GameApp();
	virtual ~GameApp();

	void run();
};

GameApp* createGameApp();

}