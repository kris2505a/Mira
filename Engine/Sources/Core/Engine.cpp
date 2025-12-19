#include "Engine.h"
#include "Input/Input.h"
#include "Logger/Log.h"
#include "Signals/WindowSignal.h"

namespace Mira {

Engine::Engine() : m_running(true) {
	m_window = std::make_unique <Window>(GetModuleHandle(nullptr), m_attrib);
	m_renderer = std::make_unique <Renderer>(m_attrib);
	m_window->signalDestination(std::bind(&Engine::signal, this, std::placeholders::_1));
}

Engine::~Engine() {

}

void Engine::render() {

}

void Engine::pulse() {

}

void Engine::signal(const Signal& s) {
	if (Signal::match<WindowCloseSignal>(s)) {
		MIRA_LOG(LOG_DEBUG, "{}", s.name());
		m_running = false;
	}
	if (Signal::match<WindowResizeSignal>(s)) {
		MIRA_LOG(LOG_DEBUG, "{}", s.name());
	}
}

void Engine::init() {
	MIRA_LOG(LOG_INFO, "Game Initialization");
	m_attrib.init();
	m_window->init();
	m_renderer->init(m_window->getHandle());
}

void Engine::shutdown() {
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

		if (Input::keyDown(Key::Escape)) {
			m_running = false;
		}

		m_renderer->flipBuffers();
	}
}

}