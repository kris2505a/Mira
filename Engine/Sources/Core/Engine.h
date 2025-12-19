#pragma once
#include "Core.h"
#include "Win32/Window.h"
#include "Renderer/Renderer.h"
#include "WindowAttributes.h"
#include <memory>
#include "Signals/Signal.h"

namespace Mira {

class MIRA_API Engine {
public:
	Engine();
	~Engine();

	void init();
	void shutdown();
	void mainloop();

private:
	void pulse();
	void render();
	void signal(const Signal& s);

private:
	std::unique_ptr <Window>     m_window;
	std::unique_ptr <Renderer>   m_renderer;
	bool                         m_running;
	WindowAttributes			 m_attrib;
};

Engine* createApp();

}