#pragma once
#include "pub/mi_swapchain.hpp"
#include <dxgi1_6.h>

namespace mira::rhw {

class D12SwapChain : public ISwapchain {
public:
    D12SwapChain(SwapchainInfo& info);
    ~D12SwapChain() override = default;

    std::vector<core::Scope<Image>> getBuffers() override;


private:
    core::ComScope<IDXGISwapChain4> mSwapchain;
    SwapchainInfo mCreateInfo;
};

}