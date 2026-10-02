#include "mi_d3d12_frame_context.hpp"
#include "mi_d3d12_helper.hpp"
#include "mi_d3d12_device.hpp"


namespace mira::rhw {

core::Scope<IFrameContext> IFrameContext::create(IDevice* device) {
    D3D12Device* nativeDevice = device->as<D3D12Device>();
    return core::createScope<D3D12FrameContext>(nativeDevice);
}

D3D12FrameContext::D3D12FrameContext(D3D12Device* device) {
    
    auto rawDevice = device->getDevice();


    HRESULT hres = rawDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mCmdAllocator));
    throwOnFailure(hres, "Failed to create command allocator");
}

ID3D12CommandAllocator* D3D12FrameContext::getCommandAllocator() const {
    return mCmdAllocator.Get();
}

core::u64 D3D12FrameContext::getFencevalue() const {
    return mFenceValue;
}

void D3D12FrameContext::setFenceValue(core::u64 value) {
    mFenceValue = value;
}



}