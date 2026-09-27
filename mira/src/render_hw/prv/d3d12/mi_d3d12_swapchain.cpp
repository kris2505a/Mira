#include "mi_d3d12_swapchain.hpp"
#include "mi_d3d12_device.hpp"
#include "mi_d3d12_helper.hpp"

namespace mira::rhw {

D12SwapChain::D12SwapChain(SwapchainInfo& info) {
    DXGI_SWAP_CHAIN_DESC1 sd = {};

    sd.Width = info.width;
    sd.Height = info.height;
    sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.Stereo = false;
    sd.SampleDesc.Count = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = info.bufferCount;
    sd.Scaling = DXGI_SCALING_NONE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    sd.Flags = 0;

    
    auto& device = info.device.as<D12Device>();
    
    core::Log::info("creating d3d12 swapchain");

    core::ComScope<IDXGISwapChain1> swapchain1;
    HRESULT hres = device.getFactory()->CreateSwapChainForHwnd(
        device.getCommandQueue(),
        info.hWnd,
        &sd,
        nullptr,
        nullptr,
        &swapchain1
    );

    throwOnFailure(hres, "Failed to create swapchain");

    hres = swapchain1->QueryInterface(IID_PPV_ARGS(&mSwapchain));
    throwOnFailure(hres, "Failed to cast IDXGISwapchain1 to IDXGISwapchain4");
}

}