#pragma once
#include "pub/mi_command_list.hpp"

#include <helpers/mi_win_hpr.hpp>
#include <helpers/mi_types.hpp>
#include <d3d12.h>

#include "mi_d3d12_device.hpp"
#include "mi_d3d12_frame_context.hpp"

namespace mira::rhw {
    
class D3D12CommandList : public ICommandList {
public:
    D3D12CommandList(D3D12Device* pDevice, D3D12FrameContext* pFrameContext);
    ~D3D12CommandList() override = default;
    void reset(IFrameContext *frameContext) override;
    void changeState(Image* img, ResourceState previous, ResourceState next) override;
    void setRenderTarget(ITargetView* view) override;
    void clearRenderTarget(ITargetView* view, std::array<core::f32, 4>& color) override;
    void close() override;

    ID3D12GraphicsCommandList* getList() const;

private:
    static D3D12_RESOURCE_STATES toD3D12State(ResourceState state);

private:
    core::ComScope<ID3D12GraphicsCommandList> mCmdList;
};

}