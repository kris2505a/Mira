#pragma once
#include "mi_engine_core.hpp"
#include <window/mi_window.hpp>
#include <mi_device.hpp>
#include <mi_swapchain.hpp>
#include "events/event.hpp"

namespace mira::engine {

class MI_ENGINE_API Engine {
public:
    void run();

private:
    void init();
    void setupCallbacks();
    void shutDown();
    void handleEvent(Event& e);

private:
    core::Scope<core::Window> mWindow;
    core::Scope<rhw::IDevice> mDevice;
    core::Scope<rhw::ISwapchain> mSwapchain;
    std::vector<core::Scope<rhw::Image>> mBuffers;
};


}
