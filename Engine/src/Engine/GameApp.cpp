#include "GameApp.h"

GameApp::GameApp() : m_window(nullptr), m_event{} {
	m_window = new Window();
}

GameApp::~GameApp() {
}

void GameApp::run() {
	while (m_window->isRunning()) {
		while (SDL_PollEvent(&m_event)) {
			if (m_event.type == SDL_QUIT)
				m_window->close();
		}
		m_window->clearBg(0u, 0u, 0u, 255u);
		
		m_window->renderAll();
	}

	delete m_window;
}