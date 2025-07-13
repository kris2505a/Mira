#pragma once
#include "MiraCore.h"
#include <MiraEngine/Window/Window.h>


namespace Mira {
class MIRA_API GameApp {

public:
	GameApp();
	virtual ~GameApp();
	void run();
};

GameApp* createGame();

} //Namespace Ends
