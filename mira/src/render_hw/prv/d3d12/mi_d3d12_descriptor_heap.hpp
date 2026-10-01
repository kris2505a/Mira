#pragma once
#include "pub/mi_descriptor_heap.hpp"
#include <helpers/mi_win_hpr.hpp>
#include <helpers/mi_types.hpp>
#include <d3d12.h>
#include "pub/mi_device.hpp"


namespace mira::rhw {

class D12DescriptorHeap : public IDescriptorHeap {
public:
    D12DescriptorHeap(core::u32 count, DescriptorType type, IDevice& device, bool shaderVisible = false);
    ~D12DescriptorHeap() override = default;

    D3D12_GPU_DESCRIPTOR_HANDLE getGPUHandle() const;
    D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandle() const;
    core::u32 getSize() const;

private:
    static D3D12_DESCRIPTOR_HEAP_TYPE getType(DescriptorType type);

private:
    core::ComScope<ID3D12DescriptorHeap> mDescriptorHeap;
    core::u32 mDescriptorSize{ 0 }; // to increment through memory for next desc
    core::u32 mDescriptorCount{ 0 };
};

}