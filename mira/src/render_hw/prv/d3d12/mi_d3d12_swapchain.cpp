#include "mi_d3d12_swapchain.hpp"
#include "mi_d3d12_device.hpp"
#include "mi_d3d12_helper.hpp"
#include "mi_d3d12_image.hpp"

namespace mira::rhw {

core::Scope<ISwapchain> ISwapchain::create(SwapchainInfo& info) {
    return core::createScope<D12SwapChain>(info);
}

D12SwapChain::D12SwapChain(SwapchainInfo& info) : mCreateInfo(info) {
    DXGI_SWAP_CHAIN_DESC1 sd = {};

    sd.Width = info.width;
    sd.Height = info.height;
    sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.Stereo = false;
    sd.SampleDesc.Count = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = info.bufferCount;
    sd.Scaling = DXGI_SCALING_STRETCH;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

    
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

std::vector<core::Scope<Image>> D12SwapChain::getBuffers() {
    core::Log::info("Retrieving images from swapchain");
    std::vector<core::Scope<Image>> images;
    images.reserve(mCreateInfo.bufferCount);
    for (core::u32 i{ 0 }; i < mCreateInfo.bufferCount; i++) {
        core::ComScope<ID3D12Resource> tmpRes;
        HRESULT hres = mSwapchain->GetBuffer(i, IID_PPV_ARGS(&tmpRes));
        throwOnFailure(hres, "Failed to retrieve swapchain images");
        images.push_back(core::createScope<D12Image>(std::move(tmpRes)));
    }
    return images;
}



}