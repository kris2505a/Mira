#pragma once
#include "Core.h"
#include "Win32/Window.h"
#include <memory>

namespace Mira {

class MIRA_API GameApp {
public:
	GameApp();
	~GameApp();

	void init();
	void shutdown();
	void mainloop();

private:
	std::unique_ptr<Window> m_window;

};

GameApp* createApp();

}