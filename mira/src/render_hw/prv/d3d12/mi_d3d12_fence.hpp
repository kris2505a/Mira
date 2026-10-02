#pragma once
#include "pub/mi_fence.hpp"
#include <helpers/mi_win_hpr.hpp>
#include <d3d12.h>

#include "mi_d3d12_device.hpp"

namespace mira::rhw {

class D3D12Fence : public IFence {
public:
	D3D12Fence(D3D12Device* device);
	~D3D12Fence() override = default;

private:
	core::ComScope<ID3D12Fence> mFence;
};

}