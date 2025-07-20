#include <MiraPreCompHeader.h>
#include "GameApp.h"
#include <MiraEngine/Logging/Log.h>
#include <MiraEngine/Event/MouseEvent.h>

namespace Mira {

GameApp::GameApp()
	: m_clock(Clock()), m_deltaTime(0.0f) {
	m_window = std::make_unique<Window>();
	m_window->setCallbackFn(std::bind(&GameApp::onEvent, this, std::placeholders::_1));
}

GameApp::~GameApp() {

}

void GameApp::onEvent(Event& e) {
	for (auto layer = m_layers.end(); layer != m_layers.begin();) {
		--layer;
		(*layer)->onEvent(e);
		if (e.isHandled())
			break;
	}
	MIRA_LOG(DEBUG, "{}", e.toString());
}

void GameApp::render() {
	SDL_SetRenderDrawColor(m_window->getRenderer(), 0u, 0u, 0u, 0u);
	SDL_RenderClear(m_window->getRenderer());
	for (auto layer = m_layers.begin(); layer != m_layers.end(); layer++) {
		(*layer)->onRender();
	}
	SDL_RenderPresent(m_window->getRenderer());
}

void GameApp::update() {
	m_window->pollEvents();
	m_deltaTime = m_clock.restart();
	for (auto layer = m_layers.begin(); layer != m_layers.end(); layer++) {
		(*layer)->onUpdate(m_deltaTime);
	}
}

void GameApp::run() {
	while (m_window->isOpen()) {
		update();
		render();
	}
}

void GameApp::pushLayer(Layer* layer) {
	m_layers.pushLayer(layer);
}

void GameApp::pushOverlay(Layer* overlay) {
	m_layers.pushOverlay(overlay);
}

} //Namespace Ends