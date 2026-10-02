#include "mi_d3d12_render_target_view.hpp"
#include "mi_d3d12_device.hpp"

namespace mira::rhw {

D12RenderTargetView::D12RenderTargetView(core::Scope<D12Image>& img, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, IDevice& dev)
    : pImage(img.get()), mRTVHandle(cpuHandle) {

    auto* device = dev.as<D12Device>()->getDevice();

    device->CreateRenderTargetView(pImage->getImage(), nullptr, cpuHandle);
}

Image& D12RenderTargetView::getImage() const {
    return *pImage;
}

}