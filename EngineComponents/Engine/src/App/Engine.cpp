#include "Engine.h"

namespace Mira {

Engine::Engine() {
	m_open = true;
	m_window = std::make_unique <Window>(1280, 720, L"Mira Engine");
	m_renderer = std::make_unique <dxr::Renderer>(m_window->getHandle());
}

void Engine::run() {
	while (m_open) {
		m_open = m_window->isOpen(); // temp fix. will fix later with events
		update();
		render();
		m_window->handleMessages();
	}
}

void Engine::update() {

}

void Engine::render() {
	dxr::Renderer::preRender();
	

	dxr::Renderer::postRender();
}

}