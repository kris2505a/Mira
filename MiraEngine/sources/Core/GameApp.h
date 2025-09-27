#pragma once
#include "Core.h"
#include "Win32/Window.h"
#include "DirectX/Renderer.h"
#include <memory>

namespace Mira {

class MIRA_API GameApp {
public:
	GameApp();
	~GameApp() = default;

	void run();

private:
	void handleMessages();
	void allocateConsole();

private:
	std::unique_ptr <Window> m_window;
	std::unique_ptr <Renderer> m_renderer;
};

GameApp* createGame();

}//namespace ends