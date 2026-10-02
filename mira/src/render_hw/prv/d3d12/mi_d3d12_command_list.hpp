#pragma once
#include "pub/mi_command_list.hpp"

#include <helpers/mi_win_hpr.hpp>
#include <helpers/mi_types.hpp>
#include <d3d12.h>

#include "mi_d3d12_device.hpp"
#include "mi_d3d12_frame_context.hpp"

namespace mira::rhw {
    
class D12CommandList : public ICommandList {
public:
    D12CommandList(D12Device* pDevice, D12FrameContext* pFrameContext);
    ~D12CommandList() override = default;

private:
    core::ComScope<ID3D12GraphicsCommandList> mCmdList;
};

}