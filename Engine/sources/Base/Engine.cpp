#include <MiraPreCompHeader.h>
#include "Engine.h"
#include "Logger/Log.h"

namespace Mira {

Engine::Engine() {
	this->init();
}

void Engine::init() {
	m_window = WindowBase::createWindow();
	m_window->setCallBack(std::bind(&Engine::event, this, std::placeholders::_1));
}

void Engine::update() {
	m_window->handleMessages();
}

void Engine::render() {

}

void Engine::event(Event& e) {
}

void Engine::run() {

	while (m_window->isOpen()) {
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