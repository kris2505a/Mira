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
	m_window    = std::make_unique <Window>(GetModuleHandle(nullptr), m_attrib);
	m_renderer  = std::make_unique <Renderer>(m_attrib);
	m_window->signalDestination(std::bind(&Engine::signal, this, std::placeholders::_1));
	m_deltaTime = 0;
	m_initialized = false;

	//temp

	m_cube = nullptr;
	m_material = nullptr;
	m_mesh = nullptr;
	m_camera = nullptr;
	
}

Engine::~Engine() {
	if (m_initialized)
		shutdown();
}

void Engine::render() {
	m_cube->render();

	for (size_t i = 0; i < m_layerStack.getLayers().size(); i++) {
		m_layerStack.getLayers()[i]->render();
	}
}

void Engine::pulse() {
	m_deltaTime = m_dtClock.elapsed();
	m_camera->pulse(m_deltaTime);
	m_cube->pulse(m_deltaTime);
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

	m_initialized = true;

	//debug
	m_material = Material::createMaterial();
	m_mesh = Mesh::cubeMesh();
	m_camera = new Camera;
	m_cube = new DbgCube(m_material, m_mesh, m_camera);

	addLayer(std::make_unique<ImGuiLayer>(m_renderer->device(), m_renderer->context(), m_window->getHandle()));
}

void Engine::shutdown() {
	Log::shutdown();

	delete m_cube;
	delete m_material;
	delete m_mesh;
	delete m_camera;

	m_attrib.shutdown();
	m_renderer->shutdown();
	m_window->shutdown();

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