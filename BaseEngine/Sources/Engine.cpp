#include <Core/Engine.hpp>
#include <Logging/Log.hpp>
#include <Events/EventDispatcher.hpp>
#include <GLFW/glfw3.h>


namespace Mira {

Engine::Engine() = default;
Engine::~Engine() = default;

void Engine::run() {
	init();
	mainLoop();
	cleanup();
}

void Engine::init() {
	m_window = std::make_unique<Window>(1600, 900, "TestRig");
	m_window->setEventCallbackFn(
        std::bind(&Engine::handleEvent, this, std::placeholders::_1)
    );
    m_graphicsFactory = mr::GraphicsFactory::create(mr::GraphicsAPI::DirectX11);
	m_renderAPI = m_graphicsFactory->createRenderAPI(m_window->getHandle());
	m_renderAPI->setClearColor(0, 1, 1, 1);
    
}

void Engine::cleanup() {
    
}

void Engine::mainLoop() {
	while (m_running) {
		glfwPollEvents();
        update();
		render();
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

    for (auto& layer : m_layerManager.getLayers()) {
        layer->render();
    }

	m_renderAPI->swap();
}

void Engine::handleEvent(Event& e) {
    Dispatcher dispatcher(e);
    dispatcher.dispatch<WindowClosedEvent>([this](WindowClosedEvent&){
        this->m_running = false;
        return  true;
    });

    dispatcher.dispatch<WindowResizedEvent>([](WindowResizedEvent& e){
        Logger::Log(LogType::Info, "{}", e.toString());
        return true;
    });

    for (auto& layer : m_layerManager.getLayers()) {
        layer->event(e);
        if(e.Handled)
            break;
    }
}

void Engine::addLayer(std::unique_ptr<Layer> layer) {
    m_layerManager.addLayer(std::move(layer));
}

}
