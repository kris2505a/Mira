#pragma once
#include "pub/mi_swapchain.hpp"
#include <dxgi1_6.h>

namespace mira::rhw {

class D3D12SwapChain : public ISwapchain {
public:
    D3D12SwapChain(SwapchainInfo& info);
    ~D3D12SwapChain() override = default;

    std::vector<core::Scope<Image>> getBuffers() override;
    core::u32 getFrameCount() const override;


private:
    core::ComScope<IDXGISwapChain4> mSwapchain;
    SwapchainInfo mCreateInfo;
};

}