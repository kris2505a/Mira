#include <PreCompHeader.h>
#include "Engine.h"
#include "Input/Input.h"
#include "Logger/Log.h"
#include "Signals/WindowSignal.h"
#include "Signals/KeyboardSignal.h"
#include "Win32/Keyboard.h"

namespace Mira {

Engine::Engine() : m_running(true) {
	m_window    = std::make_unique <Window>(GetModuleHandle(nullptr), m_attrib);
	m_renderer  = std::make_unique <Renderer>(m_attrib);
	m_window->signalDestination(std::bind(&Engine::signal, this, std::placeholders::_1));
	m_deltaTime = 0;
}

Engine::~Engine() {

}

void Engine::render() {
	for (size_t i = 0; i < m_layerStack.getLayers().size(); i++) {
		m_layerStack.getLayers()[i]->render();
	}
}

void Engine::pulse() {
	m_deltaTime = m_dtClock.elapsed();
	for (size_t i = 0; i < m_layerStack.getLayers().size(); i++) {
		m_layerStack.getLayers()[i]->pulse(m_deltaTime);
	}
}

void Engine::signal(const Signal& s) {
	if (Signal::match<WindowCloseSignal>(s)) {
		MIRA_LOG(LOG_DEBUG, "{}", s.name());
		m_running = false;
	}
	if (Signal::match<WindowResizeSignal>(s) && m_renderer->isInitialized()) {
			m_renderer->resizeCall();
	}

	for (size_t i = 0; i < m_layerStack.getLayers().size(); i++) {
		m_layerStack.getLayers()[i]->signal(s);
	}
}

void Engine::addLayer(std::unique_ptr <Layer> layer) {
	m_layerStack.addLayer(std::move(layer));
}

void Engine::init() {
	MIRA_LOG(LOG_INFO, "Game Initialization");
	Log::init();
	m_attrib.init();
	m_window->init();
	m_renderer->init(m_window->getHandle());
}

void Engine::shutdown() {
	Log::shutdown();
	m_attrib.shutdown();
	m_renderer->shutdown();
	m_window->shutdown();
	MIRA_LOG(LOG_INFO, "Game Shutdown");
}

void Engine::mainloop() {
	while (m_running) {
		m_window->handleMessages();
		m_renderer->wipeOff();
		m_renderer->bindEssentials();

		this->pulse();
		this->render();

		if (Input::keyDown(Key::Escape)) {
			m_running = false;
		}

		m_renderer->flipBuffers();
		Keyboard::endState();
	}
}

}