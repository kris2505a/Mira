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

	//temp

	m_material = nullptr;
	m_mesh = nullptr;
	
}

Engine::~Engine() {

}

void Engine::render() {

	ImGuiLayer::begin();

	for (size_t i = 0; i < m_layerStack.getLayers().size(); i++) {
		m_layerStack.getLayers()[i]->render();
	}

	ImGuiLayer::end();
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

void Engine::addLayer(Layer* layer) {
	m_layerStack.addLayer(layer);
}

void Engine::init() {
	MIRA_LOG(LOG_INFO, "Game Initialization");
	Log::init();
	m_attrib.init();
	m_window->init();
	m_renderer->init(m_window->getHandle());

	m_initialized = true;

	//debug
	m_material = Material::createMaterial();
	m_mesh = Mesh::cubeMesh();
	m_layerStack.addUI(new ImGuiLayer(m_renderer->device(), m_renderer->context(), m_window->getHandle()));
}

void Engine::shutdown() {
	Log::shutdown();

	delete m_material;
	delete m_mesh;

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