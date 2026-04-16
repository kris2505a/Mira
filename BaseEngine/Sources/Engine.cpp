#include <Core/Engine.hpp>
#include <Logging/Log.hpp>


namespace Mira {

Engine::Engine() = default;
Engine::~Engine() = default;

void Engine::run() {
	init();
	mainLoop();
	cleanup();
}

void Engine::init() {
	m_window = std::make_unique<Window>(m_eventSystem, 1600, 900, "TestRig");
	m_graphicsFactory = mr::GraphicsFactory::create(mr::GraphicsAPI::DirectX11);
	m_renderAPI = m_graphicsFactory->createRenderAPI(m_window->getHandle());
	m_renderAPI->setClearColor(0, 1, 1, 1);
}

void Engine::cleanup() {
	Logger::Log(LogType::Info, "Engine Cleanup");
}

void Engine::mainLoop() {
	while (m_running) {
		update();
		render();
		m_window->pollEvents();
		handleEvent();
	}
}

void Engine::update() {
    for (auto& layer : m_layerManager.getLayers()) {
        layer->update(1.0f);
    }
}

void Engine::render() {
	m_renderAPI->preRenderSetup();
	m_renderAPI->clear();

	m_renderAPI->swap();
}

void Engine::handleEvent() {
	while (!m_eventSystem.isQueueEmpty()) {
		auto e = m_eventSystem.getEvent();
		
        if(e.getEventType() == EventType::WindowClosed) {
            m_running = false;
        }
	}
}

void Engine::addLayer(std::unique_ptr<Layer> layer) {
    m_layerManager.addLayer(std::move(layer));
}

}
