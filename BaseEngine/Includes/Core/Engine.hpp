#pragma once
#include "Core.hpp"

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
	

private:
	int m_test = 0;
};

}