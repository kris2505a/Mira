#pragma once
#include "pub/mi_frame_context.hpp"
#include <vector>

#include <helpers/mi_win_hpr.hpp>
#include <d3d12.h>

namespace mira::rhw {

class D12FrameContext : public IFrameContext {
public:
    D12FrameContext(core::u32 frameCount, IDevice& device);
    ~D12FrameContext() override = default;

    ID3D12CommandAllocator* getCommandAllocator(core::u32 idx = 0u) const;
    core::u32 getFenceValue(core::u32 idx) const;
    void setFenceValue(core::u32 idx, core::u32 fenceValue);

private:
    std::vector<core::ComScope<ID3D12CommandAllocator>> mCmdAllocators;
    std::vector<core::u32> mFenceValues;
    core::u32 mFrameCount;
};

}