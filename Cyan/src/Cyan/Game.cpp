#include "PreCompHeaders.hpp"
#include "Game.hpp"
#include "Events/AppEvent.hpp"

namespace Cyan {

	Game::Game() {
		m_window = std::unique_ptr<GWindow>(GWindow::createWindow());
		m_isRunning = true;
	}

	Game::~Game() {

	}

	void Game::run() {

		while (m_isRunning) {
			m_window->onUpdate();
		}
	}
}