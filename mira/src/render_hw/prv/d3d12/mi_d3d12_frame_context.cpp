#include "mi_d3d12_frame_context.hpp"
#include "mi_d3d12_helper.hpp"
#include "mi_d3d12_device.hpp"


namespace mira::rhw {

core::Scope<IFrameContext> IFrameContext::create(core::u32 frameCount, IDevice& device) {
    return core::createScope<D12FrameContext>(frameCount, device);
}

D12FrameContext::D12FrameContext(core::u32 frameCount, IDevice& device)
    : mFrameCount(frameCount) {
    
    auto rawDevice = device.as<D12Device>()->getDevice();
    mCmdAllocators.reserve(mFrameCount);

    for (core::u32 i{ 0 }; i < mFrameCount; i++) {
        core::ComScope<ID3D12CommandAllocator> tmpAlloc;
        HRESULT hres = rawDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&tmpAlloc));
        throwOnFailure(hres, "Failed to create command allocator for frame: " + std::to_string(i));
        mCmdAllocators.push_back(std::move(tmpAlloc));
    }
}

ID3D12CommandAllocator* D12FrameContext::getCommandAllocator(core::u32 idx) const {
    if (idx > mCmdAllocators.size()) {
        throw std::runtime_error("Cmd Allocators not found!");
    }

    return mCmdAllocators.at(idx).Get();
}

core::u32 D12FrameContext::getFenceValue(core::u32 idx) const {
    if (idx > mFrameCount) {
        throw std::runtime_error("Invalid frame index");
    }

    return mFenceValues.at(idx);
}


}