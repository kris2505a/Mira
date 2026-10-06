#include "engine/mi_engine.hpp"
#include "core/mi_log.hpp"

MI_ENGINE

auto Engine::init() -> bool {
    auto tmpWnd = core::Window::create();
    if (!tmpWnd) {
        core::Log::error("window creation failed: {}", tmpWnd.error());
        return false;
    }
    m_window = std::move(*tmpWnd);

    setupCallback();

    return true;
}

auto Engine::run() -> void {
    bool running = true;

    m_game->init();
    while (running) {
        running = m_window->pollEvents();
        m_game->update(0.0f);
    }
}

auto Engine::attachGame(core::Scope<Game> game) -> void {
    m_game = std::move(game);
}

auto Engine::handleEvent(Event& event) -> void {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<KeyPressEvent>([](KeyPressEvent& e) {
        core::Log::debug("Key pressed: {}", e.key);
        return true;
    });

    dispatcher.dispatch<MouseMoveEvent>([](MouseMoveEvent& e) {
        core::Log::debug("({}, {})", e.x, e.y);
        return true;
    });
}

auto Engine::setupCallback() -> void {
    m_window->setKeyCallback([this](core::u32 key, bool repeat, bool down) {
        if (down) {
            KeyPressEvent e(key, repeat);
            handleEvent(e);
        }
        else {
            KeyReleaseEvent e(key);
            handleEvent(e);
        }
    });
    
    m_window->setMouseButtonCallback([this](core::u32 button, bool down) {
        if (down) {
            MouseButtonPressEvent e(button, false);
            handleEvent(e);
        }
        else {
            MouseButtonReleaseEvent e(button);
            handleEvent(e);
        }
    });

    m_window->setMouseMoveCallback([this](core::f32 x, core::f32 y) {
        MouseMoveEvent e(x, y);
        handleEvent(e);
    });

    m_window->setMouseScrollCallback([this](core::f32 delta) {
        MouseScrollEvent e(delta);
        handleEvent(e);
    });

    m_window->setResizeCallback([this](core::u32 width, core::u32 height) {
        WindowResizeEvent e(width, height);
        handleEvent(e);
    });

    m_window->setLostFocusCallback([this]() {
        WindowLostFocus e;
        handleEvent(e);
    });
}


MI_ENGINE_END