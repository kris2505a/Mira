#include <PreCompHeader.hpp>
#include "Engine.hpp"
#include "Input/Input.hpp"
#include "Logger/Log.hpp"
#include "Signals/WindowSignal.hpp"
#include "Signals/KeyboardSignal.hpp"
#include "Win32/Keyboard.hpp"
#include "Layers/ImGuiLayer.hpp"


namespace Mira {

Engine::Engine() : m_running(true) {
	m_window    = new Window(GetModuleHandle(nullptr), m_attrib);
	m_renderer  = new Renderer(m_attrib);
	m_window->signalDestination(std::bind(&Engine::signal, this, std::placeholders::_1));
	m_deltaTime = 0;
	m_initialized = false;
	m_world = nullptr;

	//temp
	m_imguiLayer = nullptr;
	m_camera = nullptr;
	m_cube = nullptr;
	m_material = nullptr;
	m_mesh = nullptr;
	
}

Engine::~Engine() {

}

void Engine::setWorld(World* world) {
	m_world = world;
	m_world->spark();
}

void Engine::render() {

	ImGuiLayer::begin();

	m_world->render(m_renderer);
	//m_cube->renderUI();

	ImGuiLayer::end();
}

void Engine::pulse() {
	m_deltaTime = m_dtClock.elapsed();
	m_world->pulse(m_deltaTime);
}

void Engine::signal(const Signal& s) {
	if (Signal::match<WindowCloseSignal>(s)) {
		MIRA_LOG(LOG_DEBUG, "{}", s.name());
		m_running = false;
	}
	if (Signal::match<WindowResizeSignal>(s) && m_renderer->isInitialized()) {
			m_renderer->resizeCall();
	}
}

void Engine::init() {
	MIRA_LOG(LOG_INFO, "Game Initialization");
	m_attrib.init();
	m_window->init();
	m_renderer->init(m_window->getHandle());
	m_imguiLayer = new ImGuiLayer(m_renderer->device(), m_renderer->context(), m_window->getHandle());
	m_world->init();

	m_initialized = true;

}

void Engine::shutdown() {

	delete m_imguiLayer;

	m_world->shutdown();
	if (m_world)
		delete m_world;

	m_attrib.shutdown();
	m_renderer->shutdown();
	m_window->shutdown();
	delete m_renderer;
	delete m_window;


	m_initialized = false;

	MIRA_LOG(LOG_INFO, "Game Shutdown");
}

void Engine::mainloop() {
	while (m_running) {

		if (!m_initialized) 
			continue;

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