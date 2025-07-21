#include <MiraPreCompHeader.h>
#include "GameApp.h"
#include <MiraEngine/Logging/Log.h>
#include <MiraEngine/Event/MouseEvent.h>
#include "MiraMacros.h"

namespace Mira {

GameApp* GameApp::s_instance = nullptr;

GameApp::GameApp()
	: m_clock(Clock()), m_deltaTime(0.0f) {

	MIRA_ASSERT(!s_instance, "Application Already Exists");
	s_instance = this;

	m_window = std::make_unique<Window>();
	m_window->setCallbackFn(std::bind(&GameApp::onEvent, this, std::placeholders::_1));
	m_renderer = std::make_unique<Renderer>(m_window->getwindow());
}

GameApp::~GameApp() {
	s_instance = nullptr;
}

Renderer* GameApp::getRenderer() const {
	return m_renderer.get();
}

GameApp* GameApp::getInstance() {
	return s_instance;
}

Window* GameApp::getWindow() const {
	return m_window.get();
}

void GameApp::onEvent(Event& e) {
	for (auto layer = m_layers.end(); layer != m_layers.begin();) {
		--layer;
		(*layer)->onEvent(e);
		if (e.isHandled())
			break;
	}
	//MIRA_LOG(INFO, "{}", e.toString());
}

void GameApp::render() {

	m_renderer->clear(0u, 0u, 0u, 0u);
	for (auto layer = m_layers.begin(); layer != m_layers.end(); layer++) {
		(*layer)->onRender(m_renderer.get());
	}
	m_renderer->renderBinded();
}

void GameApp::update() {
	m_window->pollEvents();
	m_deltaTime = m_clock.restart();
	for (auto layer = m_layers.begin(); layer != m_layers.end(); layer++) {
		(*layer)->onUpdate(m_deltaTime);
	}
	int fps = 1.0f / m_deltaTime;
	std::string title = "Mira Engine | FPS: " + std::to_string(fps);
	SDL_SetWindowTitle(m_window.get()->getwindow(), title.c_str());
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