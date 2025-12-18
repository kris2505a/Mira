#include "GameApp.h"
#include "Input/Input.h"
#include "Logger/Log.h"

namespace Mira {

GameApp::GameApp() : m_running(true) {
	m_window = std::make_unique <Window>(GetModuleHandle(nullptr), m_attrib);
	m_renderer = std::make_unique <Renderer>(m_attrib);
}

GameApp::~GameApp() {

}

void GameApp::init() {
	MIRA_LOG(LOG_INFO, "Game Initialization");
	m_attrib.init();
	m_window->init();
	m_renderer->init(m_window->getHandle());
}

void GameApp::shutdown() {
	m_attrib.shutdown();
	m_renderer->shutdown();
	m_window->shutdown();
	MIRA_LOG(LOG_INFO, "Game Shutdown");
}

void GameApp::mainloop() {
	while (m_running) {
		m_running = m_window->handleMessages();
		m_renderer->wipeOff();
		m_renderer->bindEssentials();

		if (Input::keyDown(Key::Escape)) {
			m_running = false;
		}

		m_renderer->flipBuffers();
	}
}

}