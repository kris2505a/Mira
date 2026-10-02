#include "mi_d3d12_command_list.hpp"
#include "mi_d3d12_helper.hpp"
#include "mi_d3d12_image.hpp"
#include "mi_d3d12_render_target_view.hpp"

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

    HRESULT hres = nativeCmdAlloc->Reset();
    throwOnFailure(hres, "Failed to reset cmd allocator");
    hres = mCmdList->Reset(nativeCmdAlloc, nullptr);
    throwOnFailure(hres, "Failed to reset cmd list");
}

void D3D12CommandList::changeState(Image* img, ResourceState previous, ResourceState next) {
    auto nativeImg = img->as<D3D12Image>();
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = nativeImg->getImage();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = toD3D12State(previous);
    barrier.Transition.StateAfter = toD3D12State(next);
    mCmdList->ResourceBarrier(1, &barrier);
}


D3D12_RESOURCE_STATES D3D12CommandList::toD3D12State(ResourceState state) {
    switch (state) {
        case ResourceState::Present:
            return D3D12_RESOURCE_STATE_PRESENT;

        case ResourceState::RenderTarget:
            return D3D12_RESOURCE_STATE_RENDER_TARGET;

        case ResourceState::CopySource:
            return D3D12_RESOURCE_STATE_COPY_SOURCE;

        case ResourceState::CopyDestination:
            return D3D12_RESOURCE_STATE_COPY_DEST;

        case ResourceState::VertexBuffer:
            return D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;

        case ResourceState::IndexBuffer:
            return D3D12_RESOURCE_STATE_INDEX_BUFFER;
    }

    std::unreachable();
}

void D3D12CommandList::setRenderTarget(ITargetView* view) {
    auto rtv = view->as<D3D12RenderTargetView>()->getCpuDescHandle();
    mCmdList->OMSetRenderTargets(1, &rtv, FALSE, nullptr);
}

void D3D12CommandList::clearRenderTarget(ITargetView* view, std::array<core::f32, 4>& color) {
    auto rtv = view->as<D3D12RenderTargetView>()->getCpuDescHandle();
    mCmdList->ClearRenderTargetView(rtv, color.data(), 0, nullptr);
}

void D3D12CommandList::close() {
    HRESULT hres = mCmdList->Close();
    throwOnFailure(hres, "Failed to close command list");
}

ID3D12GraphicsCommandList* D3D12CommandList::getList() const {
    return mCmdList.Get();
}


} // namespace mira::rhw