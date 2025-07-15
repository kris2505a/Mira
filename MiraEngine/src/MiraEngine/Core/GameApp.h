#pragma once
#include "MiraCore.h"
#include <MiraEngine/Window/Window.h>
#include <SDL_events.h>
#include <MiraEngine/Layer/LayerStack.h>

namespace Mira {
class MIRA_API GameApp {

public:
	GameApp();
	virtual ~GameApp();
	void run();
	void render();
	virtual void update();
	void onEvent(Event& e);
	

private:
	Window* m_window;
	LayerStack m_layers;
};

GameApp* createGame();

} //Namespace Ends
