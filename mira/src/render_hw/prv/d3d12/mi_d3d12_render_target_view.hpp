#pragma once
#include "pub/mi_target_view.hpp"

#include "mi_d3d12_image.hpp"
#include <d3d12.h>
#include "pub/mi_device.hpp"

namespace mira::rhw {

class D3D12RenderTargetView : public ITargetView {
public:
    D3D12RenderTargetView(core::Scope<D3D12Image>& image, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, IDevice& dev);
    ~D3D12RenderTargetView() override = default;
    Image& getImage() const override;

private:
    D3D12Image* pImage;
    D3D12_CPU_DESCRIPTOR_HANDLE mRTVHandle;

};

}