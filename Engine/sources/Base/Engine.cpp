#include <MiraPreCompHeader.h>
#include "Engine.h"
#include "Logger/Log.h"
#include <Events/EngineEvent.h>

namespace Mira {

Engine::Engine() {
	m_window = std::make_unique <Win32Window>(1600u, 900u, L"MiraEngine");
	m_window->setCallBack(std::bind(&Engine::event, this, std::placeholders::_1));
}

void Engine::update() {
	m_window->handleMessages();
}

void Engine::render() {
	
}

void Engine::event(Event& e) {
	EventDispatcher dispatcher(e);
	//MIRA_LOG(LOG_INFO, "{}", e.print());
	dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { m_window->close(); return true; });
}

void Engine::run() {

	while (m_window->isOpen()) {
		this->update();
		this->render();
	}
}


Engine::~Engine() {
	
}

}