#include <MiraPreCompHeader.h>
#include "GameApp.h"
#include <MiraEngine/Logging/Log.h>
#include <MiraEngine/Event/MouseEvent.h>

namespace Mira {

GameApp::GameApp() {
	m_window = std::make_unique<Window>();
	m_window->setCallbackFn([this](Event& e) {onEvent(e); });
}

GameApp::~GameApp() {

}

void GameApp::onEvent(Event& _e) {
	for (auto layer = m_layers.end(); layer != m_layers.begin();) {
		--layer;
		(*layer)->onEvent(_e);
		if (_e.isHandled())
			break;
	}
}

void GameApp::render() {
	SDL_SetRenderDrawColor(m_window->getRenderer(), 0u, 255u, 255u, 255u);
	SDL_RenderClear(m_window->getRenderer());
	for (auto layer = m_layers.begin(); layer != m_layers.end(); layer++) {
		(*layer)->onRender();
	}
	SDL_RenderPresent(m_window->getRenderer());
}

void GameApp::update() {
	m_window->pollEvents();
	float time = 60.f;
	float deltaTime = 1 / time;

	for (auto layer = m_layers.begin(); layer != m_layers.end(); layer++) {
		(*layer)->onUpdate(deltaTime);
	}
}

void GameApp::run() {
	while (m_window->isOpen()) {
		update();
		render();
	}
}

void GameApp::pushLayer(Layer* _layer) {
	m_layers.pushLayer(_layer);
}

void GameApp::pushOverlay(Layer* _overlay) {
	m_layers.pushOverlay(_overlay);
}

} //Namespace Ends