#include "mi_d3d12_descriptor_heap.hpp"
#include "mi_d3d12_device.hpp"
#include "mi_d3d12_helper.hpp"

namespace mira::rhw {

D12DescriptorHeap::D12DescriptorHeap(core::u32 count, DescriptorType type, IDevice& device, bool shaderVisible)
    : mDescriptorCount(count) {
    
    auto descType = getType(type);
    
    D3D12_DESCRIPTOR_HEAP_DESC dhd = {};
    dhd.NumDescriptors = count;
    dhd.Type = descType;

    if (shaderVisible) {
        dhd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    }
    else {
        dhd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    }
    auto* rawDevice = device.as<D12Device>().getDevice();

    HRESULT hres = rawDevice->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(&mDescriptorHeap));
    throwOnFailure(hres, "Failed to create ID3D12DescriptorHeap");

    mDescriptorSize = rawDevice->GetDescriptorHandleIncrementSize(descType);
}

D3D12_DESCRIPTOR_HEAP_TYPE D12DescriptorHeap::getType(DescriptorType type) {
    switch (type) {
    case DescriptorType::RTV:
        return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        
    case DescriptorType::DSV:
        return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    }
    throw std::runtime_error("Unknown Descriptor type!");
}

}