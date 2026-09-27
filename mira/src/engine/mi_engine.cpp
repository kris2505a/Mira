#include "mi_engine.hpp"
#include <log/mi_log.hpp>


namespace mira::engine {

void Engine::init() {
    mWindow = std::make_unique<core::Window>();
    mDevice = rhw::IDevice::create();
}

void Engine::setupCallbacks() {
    mWindow->setKeyCallback([this](core::u32 key, bool repeat, bool down) {
        if (down) {
            KeyPressEvent e(key, repeat);
            handleEvent(e);
        }
        else {
            KeyReleaseEvent e(key);
            handleEvent(e);
        }
    });
    
    mWindow->setMouseButtonCallback([this](core::u32 button, bool down) {
        if (down) {
            MouseButtonPressEvent e(button, false);
            handleEvent(e);
        }
        else {
            MouseButtonReleaseEvent e(button);
            handleEvent(e);
        }
    });

    mWindow->setMouseMoveCallback([](core::f32 x, core::f32 y) {
        // core::Log::debug("MousePos: {}, {}", x, y);
    });

    mWindow->setMouseScrollCallback([](core::f32 delta) {
        // core::Log::debug("ScrollDelta: {}", delta);
    });

    mWindow->setResizeCallback([](core::u32 width, core::u32 height) {
        // core::Log::debug("Resized: {}x{}", width, height);
    });

    mWindow->setLostFocusCallback([]() {
        // core::Log::debug("Window Lost focus");
    });

}

void Engine::run() {
    init();
    setupCallbacks();

    bool running = true;

    while (running) {
        running = mWindow->pollEvents();
    }
}

void Engine::handleEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<KeyPressEvent>([](KeyPressEvent& e) {
        core::Log::debug("KeyPressed: {}", e.key);
        return true;
    });

    dispatcher.dispatch<KeyReleaseEvent>([](KeyReleaseEvent&e) {
        core::Log::debug("Key Released: {}", e.key);
        return true;
    });
}

}
