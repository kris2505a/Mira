#include "mi_d3d12_command_list.hpp"
#include "mi_d3d12_helper.hpp"

namespace mira::rhw {

core::Scope<ICommandList> ICommandList::create(IFrameContext* frameContext, IDevice* device) {
    auto nativeDevice = device->as<D12Device>();
    auto nativeFrameContext = frameContext->as<D12FrameContext>();

    return core::createScope<D12CommandList>(nativeDevice, nativeFrameContext);
}

D12CommandList::D12CommandList(D12Device* device, D12FrameContext* context) {

    auto rawDev = device->getDevice();
    auto cmdAlloc0 = context->getCommandAllocator(0);
    
    HRESULT hres = rawDev->CreateCommandList(
        0, 
        D3D12_COMMAND_LIST_TYPE_DIRECT, 
        cmdAlloc0, 
        nullptr, 
        IID_PPV_ARGS(&mCmdList)
    );

    throwOnFailure(hres, "Failed to create Command List");
    mCmdList->Close();
}


}