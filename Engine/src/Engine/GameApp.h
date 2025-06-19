#pragma once
#include "Core.h"

class API GameApp {

public:
	GameApp();
	virtual ~GameApp();

	virtual void run();
};

GameApp* createGameApp();