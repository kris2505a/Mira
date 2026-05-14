#include "MiraPch.h"
#include "Mira/Logger/Logger.h"
#include "Engine.h"
#include "Mira/Event/WindowEvent.h"
#include "Mira/Event/KeyboardEvent.h"
#include "Mira/Event/MouseEvent.h"

#include "Mira/Input/Input.h"

namespace Mira {

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

    Renderer::clearColor(0.02f, 0.04f, 0.10f, 1.0f);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    m_vbo = VertexBuffer::create(vertices, 3, 3 * sizeof(float));

    uint32_t indices[] = {
        0, 2, 1
    };

    m_ibo = IndexBuffer::create(indices, 3);

    InputLayout layout;
    layout.addLayout({
        "POSITION",
        LayoutDataType::Float,
        3,
        0
    });

    m_shader = Shader::create(L"Def", layout);
}

void Engine::shutDown() {
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
    m_vbo->bind();
    m_ibo->bind();
    m_shader->bind();

    if (Input::isKeyHeld(Key::Space)) {
        Logger::log(LogType::Debug, "Space Bar Pressed");
    }

}

void Engine::render() {
    Renderer::preSetup();

    Renderer::getRHI()->drawIndexed(m_ibo->getCount());

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
        return true;
    });

    dispatcher.dispatch<KeyReleaseEvent>([](KeyReleaseEvent& event) {
        Input::setKeyState(static_cast<Key>(event.getKey()), Input::State::Up);
        return true;
    });

    dispatcher.dispatch<MouseButtonPressEvent>([](MouseButtonPressEvent& event) {
        Input::setButtonState(static_cast<Button>(event.getButton()), Input::State::Down);
        return true;
    });

    dispatcher.dispatch<MouseButtonReleaseEvent>([](MouseButtonReleaseEvent& event) {
        Input::setButtonState(static_cast<Button>(event.getButton()), Input::State::Up);
        return true;
    });

    dispatcher.dispatch<MouseMoveEvent>([](const MouseMoveEvent& event) {
        Input::mouseMove({event.getX(), event.getY()});
        return true;
    });

    dispatcher.dispatch<MouseScrollEvent>([](MouseScrollEvent& event) {
        Input::mouseScroll(event.getOffset());
        return true;
    });

    dispatcher.dispatch<WindowLostFocusEvent>([](WindowLostFocusEvent& e) {
        Input::resetState();
        return true;
    });

}

void Engine::pollEvent() {
    m_window->pollEvents();
}

}
