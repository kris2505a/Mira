#pragma once
#include "MiraCore.h"
#include <MiraEngine/Window/Window.h>
#include <SDL_events.h>

namespace Mira {
class MIRA_API GameApp {

public:
	GameApp();
	virtual ~GameApp();
	void run();
	void render();
	virtual void update();

};

GameApp* createGame();

} //Namespace Ends
