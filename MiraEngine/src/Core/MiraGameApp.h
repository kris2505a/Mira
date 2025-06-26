#pragma once

#include "MiraCore.h"

namespace Mira {
class MIRA_API GameApp {
public:
	GameApp();
	virtual ~GameApp();

	void run();
};

GameApp* createGameApp();

}