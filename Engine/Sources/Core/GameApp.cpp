#include "GameApp.h"

namespace Mira {

GameApp::GameApp() {
	m_window = std::make_unique <Window>(GetModuleHandle(nullptr));
}

GameApp::~GameApp() {

}

void GameApp::init() {
	m_window->create();
}

void GameApp::shutdown() {
	m_window->destroy();
}

void GameApp::mainloop() {
	while (true) {
		m_window->handleMessages();
	}
}

}