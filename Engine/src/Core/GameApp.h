#pragma once
#include "Core.h"
#include "Window.h"

class API GameApp {

private:
	Window* m_window;
	SDL_Event m_event;

public:
	GameApp();
	virtual ~GameApp();

	void run();
	void render();
	virtual void update(const float& deltaTime);
};

GameApp* createGameApp();