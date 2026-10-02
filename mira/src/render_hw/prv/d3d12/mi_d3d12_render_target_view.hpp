#pragma once
#include "pub/mi_target_view.hpp"

#include "mi_d3d12_image.hpp"
#include <d3d12.h>
#include "mi_d3d12_device.hpp"

namespace mira::rhw {

class D3D12RenderTargetView : public ITargetView {
public:
    D3D12RenderTargetView(D3D12Image* img, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, D3D12Device* dev);
    ~D3D12RenderTargetView() override = default;
    Image& getImage() const override;
    D3D12_CPU_DESCRIPTOR_HANDLE getCpuDescHandle();

private:
    D3D12Image* pImage;
    D3D12_CPU_DESCRIPTOR_HANDLE mRTVHandle;

};

}