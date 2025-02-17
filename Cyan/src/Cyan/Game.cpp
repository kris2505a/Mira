#include "PreCompHeaders.hpp"
#include "Game.hpp"
#include "GLFW/glfw3.h"
#include "Log.hpp"

namespace Cyan {

#define BIND_EVENT_CALLBACK(X) std::bind(&Game::X, this, std::placeholders::_1)

	Game::Game() {
		m_window = std::unique_ptr<GWindow>(GWindow::createWindow());
		m_isRunning = true;
		m_window->setEventCallBack(BIND_EVENT_CALLBACK(onEvent));
	}

	Game::~Game() {

	}

	void Game::run() {

		while (m_isRunning) {

			glClearColor(0.f, 1.f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}
	}

	void Game::onEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<windowCloseEvent>(BIND_EVENT_CALLBACK(onClose));
		CYAN_LOG(CY_INFO, event.toString());
	}

	bool Game::onClose(windowCloseEvent& event) {
		m_isRunning = false;
		return true;
	}

}