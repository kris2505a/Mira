#include "MiraPch.hpp"
#include "Mira/Logger/Logger.hpp"
#include "Engine.hpp"
#include "Mira/Event/WindowEvent.hpp"
#include "Mira/Event/KeyboardEvent.hpp"
#include "Mira/Event/MouseEvent.hpp"

#include "Mira/Input/Input.hpp"

#include "Mira/EngineComponents/Clock.hpp"
#include "Mira/Stats/EngineStats.hpp"


#include <DirectXMath.h>
#define TO_RAD(x) DirectX::XMConvertToRadians(x)

namespace Mira {

Engine* Engine::s_instance = nullptr;


Engine::Engine() {

    if (s_instance) {
        throw std::runtime_error("Instance of engine already exists!");
    }
    s_instance = this;

    Logger::log(LogType::Info, "Engine Initializing...");


    WindowAttributes attribs(1280, 720, "Mira", [this](Event& e){ handleEvent(e); });
    attribs.width = 1280;
    attribs.height = 720;
    attribs.title = "Mira";
    m_window = createScope<WIN32Window>(attribs);

    EngineStats::WindowProperties::setWindowHandle(m_window->getHandle());
    EngineStats::WindowProperties::setSize(m_window->getWidth(), m_window->getHeight());


    m_renderer = createScope<Renderer>();
    
    EngineStats::DeltaTime::initialize();
    
    Renderer::clearColor(0.02f, 0.04f, 0.10f, 1.0f);


}

Engine::~Engine() {


    Logger::log(LogType::Info, "Engine Shutting Down...");
}

void Engine::run() {

    mainLoop();

}

void Engine::update() {

}


void Engine::mainLoop() {
    Logger::log(LogType::Info, "Engine Running...");
    while (m_running) {
        pollEvent();
        EngineStats::DeltaTime::updateDeltaTime();

        Renderer::preSetup();

        const auto& layers = m_layerManager.getLayers();

        for (auto it = m_layerManager.getLayers().rbegin(); it != layers.rend(); it++) {
            (*it)->update();
        }


        update();


        for (auto it = m_layerManager.getLayers().rbegin(); it != layers.rend(); it++) {
            (*it)->render();
        }

        Renderer::postSetup();


        Input::endState();
    }
}


LayerManager& Engine::getLayerManager() {
    return m_layerManager;
}

void Engine::handleEvent(Event& e) {
    EventDispatcher dispatcher(e);

    dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) {
        m_running = false;
        return true;
    });

    dispatcher.dispatch<WindowResizeEvent>([](WindowResizeEvent& event) {
        Renderer::resize(event.getWidth(), event.getHeight());
        EngineStats::WindowProperties::setSize(event.getWidth(), event.getHeight());
        return false;
    });

    dispatcher.dispatch<KeyPressEvent>([](KeyPressEvent& event) {
        Input::setKeyState(static_cast<Key>(event.getKey()), Input::State::Down);
        return false;
    });

    dispatcher.dispatch<KeyReleaseEvent>([](KeyReleaseEvent& event) {
        Input::setKeyState(static_cast<Key>(event.getKey()), Input::State::Up);
        return false;
    });

    dispatcher.dispatch<MouseButtonPressEvent>([](MouseButtonPressEvent& event) {
        Input::setButtonState(static_cast<Button>(event.getButton()), Input::State::Down);
        return false;
    });

    dispatcher.dispatch<MouseButtonReleaseEvent>([](MouseButtonReleaseEvent& event) {
        Input::setButtonState(static_cast<Button>(event.getButton()), Input::State::Up);
        return false;
    });

    dispatcher.dispatch<MouseMoveEvent>([](const MouseMoveEvent& event) {
        Input::mouseMove({event.getX(), event.getY()});
        return false;
    });

    dispatcher.dispatch<MouseScrollEvent>([](MouseScrollEvent& event) {
        Input::mouseScroll(event.getOffset());
        return false;
    });

    dispatcher.dispatch<WindowLostFocusEvent>([](WindowLostFocusEvent& e) {
        Input::resetState();
        return true;
    });

    const auto& layers = m_layerManager.getLayers();

    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        (*it)->handleEvent(e);
        if (e.handled) {
            break;
        }
    }
}

Engine& Engine::get() {
    return (*s_instance);
}

Window& Engine::getWindow() const {
    return *m_window.get();
}

void Engine::pollEvent() {
    m_window->pollEvents();
}


}
