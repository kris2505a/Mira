#pragma once
#include "Core.h"
#include "Win32/Window.h"
#include "Renderer/Renderer.h"
#include "WindowAttributes.h"
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
	std::unique_ptr <Window>     m_window;
	std::unique_ptr <Renderer>   m_renderer;
	bool                         m_running;
	WindowAttributes			 m_attrib;
};

GameApp* createApp();

}