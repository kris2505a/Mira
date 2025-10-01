#include <MiraPreCompHeader.h>
#include "Engine.h"
#include "Logger/Log.h"

namespace Mira {

Engine::Engine() {
	this->init();
}

void Engine::init() {
	m_window = WindowBase::createWindow();
	MIRA_LOG(LOG_DEBUG, "Engine init successful with code {}", 69);
}

void Engine::update() {
	m_window->handleMessages();
}

void Engine::render() {

}

void Engine::run() {

	while (true) {
		this->update();
		this->render();
	}
}

void Engine::shutdown() {

}

Engine::~Engine() {
	this->shutdown();
}

}