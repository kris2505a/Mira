#include <Core/Engine.hpp>
#include <Logging/Log.hpp>
#include <Events/EventDispatcher.hpp>
#include <Input/Input.hpp>

namespace Mira {

Engine::Engine() = default;
Engine::~Engine() = default;

void Engine::run() {
	init();
	mainLoop();
	cleanup();
}

void Engine::init() {
    m_window = Window::createWindow(1280, 720, "Test Rig");
	m_window->setEventCallbackFn(
        std::bind(&Engine::handleEvent, this, std::placeholders::_1)
    );
    m_graphicsFactory = mr::GraphicsFactory::create(mr::GraphicsAPI::DirectX11);
	m_renderAPI = m_graphicsFactory->createRenderAPI(m_window->getHandle());

    mr::GPUInfo info = m_renderAPI->getGPUInfo();

    std::string vendor;

    switch (info.vendorId) {
    case 0x10DE: 
        vendor = "NVIDIA";
        break;

    case 0x1002:
        vendor = "AMD";
        break;

    case 0x8086:
        vendor = "Intel";
        break;

    default:
        vendor = "Unknown";
        break;
    }

    Logger::Log(LogType::Info, "GPU: {}", info.name);
    Logger::Log(LogType::Info, "Vendor: {} ({})", vendor, info.vendorId);
    Logger::Log(LogType::Info, "Device Id: {}", info.deviceId);
    Logger::Log(LogType::Info, "VRAM: {} MB", info.dedicatedVRAM);
    Logger::Log(LogType::Info, "Shared RAM: {} MB", info.sharedRam);

}

void Engine::cleanup() {
    //////////////////////////////////
    ///so far nothing to clean up////
    /////////////////////////////////
}

void Engine::mainLoop() {
	while (m_running) {
        m_window->pollEvents();
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
    dispatcher.dispatch<WindowClosedEvent>([this](WindowClosedEvent& e){
        Logger::Log(LogType::Info, "{}", e.toString());
        this->m_running = false;
        return  true;
    });

    dispatcher.dispatch<WindowResizedEvent>([this](WindowResizedEvent& e){
        Logger::Log(LogType::Info, "{}", e.toString());
        this->m_renderAPI->resize(e.getWidth(), e.getHeight());
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
