#include "mi_engine.hpp"
#include <log/mi_log.hpp>


namespace mira::engine {

void Engine::init() {
    mWindow = std::make_unique<core::Window>();
    mDevice = rhw::IDevice::create();

    rhw::SwapchainInfo info {
        .bufferCount = 2, 
        .width = 1280u,
        .height = 720u,
        .hWnd = mWindow->getWin32Handle(),
        .device = *mDevice.get()
    };

    mSwapchain = rhw::ISwapchain::create(info);
    mBuffers = mSwapchain->getBuffers();
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

    mWindow->setMouseMoveCallback([this](core::f32 x, core::f32 y) {
        MouseMoveEvent e(x, y);
        handleEvent(e);
    });

    mWindow->setMouseScrollCallback([this](core::f32 delta) {
        MouseScrollEvent e(delta);
        handleEvent(e);
    });

    mWindow->setResizeCallback([this](core::u32 width, core::u32 height) {
        WindowResizeEvent e(width, height);
        handleEvent(e);
    });

    mWindow->setLostFocusCallback([this]() {
        WindowLostFocus e;
        handleEvent(e);
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
        // core::Log::debug("KeyPressed: {}", e.key);
        return true;
    });

    dispatcher.dispatch<KeyReleaseEvent>([](KeyReleaseEvent&e) {
        // core::Log::debug("Key Released: {}", e.key);
        return true;
    });
}

}
