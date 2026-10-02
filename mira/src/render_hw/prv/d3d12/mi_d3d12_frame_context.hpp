#pragma once
#include "pub/mi_frame_context.hpp"

#include <helpers/mi_win_hpr.hpp>
#include "mi_d3d12_device.hpp"
#include <d3d12.h>

namespace mira::rhw {

class D3D12FrameContext : public IFrameContext {
public:
    D3D12FrameContext(D3D12Device* device);
    ~D3D12FrameContext() override = default;

    ID3D12CommandAllocator* getCommandAllocator() const;
    core::u32 getFenceValue() const;
    void setFenceValue();

private:
    core::ComScope<ID3D12CommandAllocator> mCmdAllocator;
    core::u32 mFenceValue;
};

}