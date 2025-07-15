#include <MiraPreCompHeader.h>
#include "GameApp.h"
#include <MiraEngine/Logging/Log.h>
#include <MiraEngine/Event/MouseEvent.h>

namespace Mira {

GameApp::GameApp() {
	m_window = new Window();
	MouseButtonPressed e(15);
	MIRA_ELOG(DEBUG, "{}", e.toString());
}

GameApp::~GameApp() {
	delete m_window;
}

void GameApp::render() {
	SDL_SetRenderDrawColor(m_window->getRenderer(), 0u, 255u, 255u, 255u);
	SDL_RenderClear(m_window->getRenderer());

	SDL_RenderPresent(m_window->getRenderer());
}

void GameApp::update() {
	m_window->pollEvents();
}

void GameApp::run() {
	while (m_window->isOpen()) {
		update();
		render();
	}
}

} //Namespace Ends