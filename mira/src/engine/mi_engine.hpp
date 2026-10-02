#pragma once

#include <array>

#include "mi_engine_core.hpp"
#include <window/mi_window.hpp>
#include <mi_device.hpp>
#include <mi_swapchain.hpp>
#include <mi_frame_context.hpp>
#include <mi_command_list.hpp>
#include "events/event.hpp"
#include <mi_descriptor_heap.hpp>
#include <mi_target_view.hpp>
#include <mi_fence.hpp>

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
    core::Scope<rhw::IDescriptorHeap> mDescHeap;
    std::vector<core::Scope<rhw::ITargetView>> mRTV;

    std::vector<core::Scope<rhw::IFrameContext>> mFrameContexts;
    core::Scope<rhw::ICommandList> mCmdList;
    core::Scope<rhw::IFence> mFence;

    std::array<core::f32, 4> mClearColor;

};


}
