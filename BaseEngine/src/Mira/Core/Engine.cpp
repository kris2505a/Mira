#include "MiraPch.hpp"
#include "Mira/Logger/Logger.hpp"
#include "Engine.hpp"
#include "Mira/Event/WindowEvent.hpp"
#include "Mira/Event/KeyboardEvent.hpp"
#include "Mira/Event/MouseEvent.hpp"

#include "Mira/Input/Input.hpp"

#include "Mira/EngineComponents/Clock.hpp"
#include "Mira/Stats/EngineStats.hpp"


#include <imgui.h>

#include <DirectXMath.h>
#define TO_RAD(x) DirectX::XMConvertToRadians(x)

namespace Mira {


namespace dx = DirectX;

Engine::Engine() {

    WindowAttributes attribs(1280, 720, "Mira", [this](Event& e){ handleEvent(e); });
    attribs.width = 1280;
    attribs.height = 720;
    attribs.title = "Mira";
    m_window = createScope<WIN32Window>(attribs);

    m_renderer = createScope<Renderer>();
}

void Engine::run() {
    initialize();
    mainLoop();
    shutDown();
}

void Engine::initialize() {

    Logger::log(LogType::Info, "Engine Initializing...");

    Renderer::initialize(m_window->getHandle(), m_window->getWidth(), m_window->getHeight());
    
    EngineStats::DeltaTime::initialize();

    Renderer::clearColor(0.02f, 0.04f, 0.10f, 1.0f);

    component.mesh = InstanceManager::createQuadMesh();

    component.material = InstanceManager::createMaterial("Def");

    component.modelMatrix = dx::XMMatrixScaling(200.0f, 200.0f, 1.0f) *
                            dx::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

    component.color = { 1.0f, 0.0f, 0.0f, 1.0f };
    
    camera.setViewWidthHeight(static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    Renderer::getRHI()->setupImGui();
}

void Engine::shutDown() {
    Renderer::getRHI()->shutDownImGui();
    ImGui::DestroyContext();
    Renderer::shutDown();
    Logger::log(LogType::Info, "Engine Shutting Down...");
}

void Engine::mainLoop() {
    Logger::log(LogType::Info, "Engine Running...");
    while (m_running) {
        pollEvent();
        update();
        render();
        Input::endState();
    }
}

void Engine::update() {

    EngineStats::DeltaTime::updateDeltaTime();


    auto cameraPos = camera.getPosition();
    float speed = 5.0f;

    if (Input::isKeyDown(Key::Left) || Input::isKeyHeld(Key::Left)) {
        cameraPos.x -= speed;
    }

    if (Input::isKeyDown(Key::Right) || Input::isKeyHeld(Key::Right)) {
        cameraPos.x += speed;
    }

    if (Input::isKeyDown(Key::Up) || Input::isKeyHeld(Key::Up)) {
        cameraPos.y += speed;
    }

    if (Input::isKeyDown(Key::Down) || Input::isKeyHeld(Key::Down)) {
        cameraPos.y -= speed;
    }

    camera.setPosition(cameraPos);

}

void Engine::render() {
    Renderer::preSetup();
    Renderer::useCamera(camera);

    Renderer::submit(component);

    Renderer::getRHI()->beginImGuiFrame();
    ImGui::NewFrame();

    ImGui::Begin("Greetings");
    ImGui::Text("Vanakkam da mapla, Engine lerunthu...");
    ImGui::End();

    ImGui::Render();
    Renderer::getRHI()->endImGuiFrame();


    Renderer::postSetup();
}

void Engine::handleEvent(Event& e) {
    EventDispatcher dispatcher(e);

    dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) {
        m_running = false;
        return true;
    });

    dispatcher.dispatch<WindowResizeEvent>([](WindowResizeEvent& event) {
        Renderer::resize(event.getWidth(), event.getHeight());
        return true;
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

void Engine::pollEvent() {
    m_window->pollEvents();
}


}
