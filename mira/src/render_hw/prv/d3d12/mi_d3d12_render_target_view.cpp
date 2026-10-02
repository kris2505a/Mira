#include "mi_d3d12_render_target_view.hpp"
#include "mi_d3d12_device.hpp"
#include "mi_d3d12_descriptor_heap.hpp"

namespace mira::rhw {

std::vector<core::Scope<ITargetView>> ITargetView::create(std::vector<core::Scope<Image>>& images, IDescriptorHeap* heap, IDevice* device) {
    auto nativeDescHeap = heap->as<D3D12DescriptorHeap>();

    auto size = nativeDescHeap->getSize();

    std::vector<core::Scope<ITargetView>> views;
    views.reserve(images.size());

    D3D12_CPU_DESCRIPTOR_HANDLE handle = nativeDescHeap->getCPUHandle();

    auto nativeDevice = device->as<D3D12Device>();

    for (core::u32 i{ 0 }; i < images.size(); i++) {
        auto nativeImg = images.at(i)->as<D3D12Image>();
        auto rtv = core::createScope<D3D12RenderTargetView>(nativeImg, handle, nativeDevice);
        views.push_back(std::move(rtv));
        handle.ptr += size;
    }

    return views;    
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12RenderTargetView::getCpuDescHandle() {
    return mRTVHandle;
}



D3D12RenderTargetView::D3D12RenderTargetView(D3D12Image* img, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, D3D12Device* dev)
    : pImage(img), mRTVHandle(cpuHandle) {

    auto* device = dev->getDevice();

    device->CreateRenderTargetView(pImage->getImage(), nullptr, cpuHandle);
}

Image& D3D12RenderTargetView::getImage() const {
    return *pImage;
}

}