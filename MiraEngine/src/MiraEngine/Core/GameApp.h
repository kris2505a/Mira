#pragma once
#include "MiraCore.h"
#include <MiraEngine/Window/Window.h>
#include <SDL_events.h>
#include <MiraEngine/Layer/LayerStack.h>
#include <memory>
#include <MiraEngine/Clock/Clock.h>

namespace Mira {
class MIRA_API GameApp {

public:
	GameApp();
	virtual ~GameApp();
	void run();
	void render();
	virtual void update();
	void onEvent(Event& e);
	void pushLayer(Layer* layer);
	void pushOverlay(Layer* overlay);
	

private:
	std::unique_ptr<Window> m_window;
	LayerStack m_layers;
	Clock m_clock;
	float m_deltaTime;
};

GameApp* createGame();

} //Namespace Ends
