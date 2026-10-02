#pragma once
#include "mi_rhw_core.hpp"
#include <helpers/mi_types.hpp>
#include <helpers/mi_win_hpr.hpp>
#include "mi_device.hpp"
#include <vector>

#include "mi_image.hpp"

namespace mira::rhw {

struct SwapchainInfo {
    core::u32 bufferCount;
    core::u32 width;
    core::u32 height;
    HWND hWnd;
    IDevice& device;
};

class MI_RENDER_API ISwapchain {
public:
    ISwapchain() = default;
    virtual ~ISwapchain() = default;

    virtual std::vector<core::Scope<Image>> getBuffers() = 0;
    virtual core::u32 getFrameCount() const = 0;

    static core::Scope<ISwapchain> create(SwapchainInfo& info);

};


}