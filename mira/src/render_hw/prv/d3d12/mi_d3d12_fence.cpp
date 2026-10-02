#pragma once
#include "mi_d3d12_fence.hpp"
#include "mi_d3d12_helper.hpp"

namespace mira::rhw {

core::Scope<IFence> IFence::create(IDevice* device) {
    auto nativeDevice = device->as<D3D12Device>();
    return core::createScope<D3D12Fence>(nativeDevice);
}

D3D12Fence::D3D12Fence(D3D12Device* device) {
    pCmdQueue = device->getCommandQueue();

    HRESULT hres = device->getDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
    throwOnFailure(hres, "Failed to create fence");
}

void D3D12Fence::signal(core::u64 value) {
    HRESULT hres = pCmdQueue->Signal(mFence.Get(), value);
    throwOnFailure(hres, "Failed to signal fence");
}

void D3D12Fence::wait(core::u64 fenceValue) {
    if (mFence->GetCompletedValue() < fenceValue) {
        HANDLE event = CreateEventW(
            nullptr,
            FALSE,
            FALSE,
            nullptr
        );

        HRESULT hres = mFence->SetEventOnCompletion(fenceValue, event);
        throwOnFailure(hres, "Failed to set event on completion");
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }
}


}