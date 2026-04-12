#pragma once
#include "Core.hpp"
#include <Events/EventSystem.hpp>

namespace Mira {

class MIRA_API Engine {
public:
	Engine();
	~Engine();
	void run();

private:
	void init();
	void cleanup();
	void mainLoop();
	void update();
	void render();
	void handleEvent();
	

private:
	int m_test					= 0;
	EventSystem m_eventSystem	= {};
	bool m_running				= true;
};

}