#include "GameApp.h"
#include "Input/Input.h"
#include "Logger/Log.h"

namespace Mira {

GameApp::GameApp() : m_running(true) {
	m_window = std::make_unique <Window>(GetModuleHandle(nullptr));
}

GameApp::~GameApp() {

}

void GameApp::init() {
	MIRA_LOG(LOG_INFO, "Game Initialization");
	m_window->create();
}

void GameApp::shutdown() {
	m_window->destroy();
	MIRA_LOG(LOG_INFO, "Game Shutdown");
}

void GameApp::mainloop() {
	while (m_running) {
		m_running = m_window->handleMessages();

		if (Input::keyDown(Key::Escape)) {
			m_running = false;
		}
	}
}

}