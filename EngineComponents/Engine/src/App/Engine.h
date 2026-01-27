#pragma once
#include "Window/Window.h"
#include <Renderer.h>

namespace Mira {

class Engine {
public:
	Engine();
	~Engine() = default;
	void run();

private:
	void update();
	void render();

private:
	std::unique_ptr <Window> m_window;
	std::unique_ptr <dxr::Renderer> m_renderer;
	bool m_open;
};

}