#include "mi_d3d12_command_list.hpp"
#include "mi_d3d12_helper.hpp"

namespace mira::rhw {

core::Scope<ICommandList> ICommandList::create(IFrameContext* frameContext, IDevice* device) {
    auto nativeDevice = device->as<D3D12Device>();
    auto nativeFrameContext = frameContext->as<D3D12FrameContext>();

    return core::createScope<D3D12CommandList>(nativeDevice, nativeFrameContext);
}

D3D12CommandList::D3D12CommandList(D3D12Device* device, D3D12FrameContext* context) {

    auto rawDev = device->getDevice();
    auto cmdAlloc0 = context->getCommandAllocator();
    
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
void D3D12CommandList::reset(IFrameContext *frameContext) {
    auto nativeCmdAlloc = frameContext->as<D3D12FrameContext>()->getCommandAllocator();

    nativeCmdAlloc->Reset();
    mCmdList->Reset(nativeCmdAlloc, nullptr);
}

} // namespace mira::rhw