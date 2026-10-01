#pragma once
#include "pub/mi_target_view.hpp"

#include "mi_d3d12_image.hpp"
#include <d3d12.h>
#include "pub/mi_device.hpp"

namespace mira::rhw {

class D12RenderTargetView : public ITargetView {
public:
    D12RenderTargetView(core::Scope<D12Image>& image, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, IDevice& dev);
    ~D12RenderTargetView() override = default;
    Image& getImage() const override;

private:
    D12Image* pImage;
    D3D12_CPU_DESCRIPTOR_HANDLE mRTVHandle;

};

}