#include "mi_d3d12_descriptor_heap.hpp"
#include "mi_d3d12_helper.hpp"

namespace mira::rhw {

core::Scope<IDescriptorHeap> IDescriptorHeap::create(core::u32 count, DescriptorType type, IDevice* device, bool shaderVisible) {
    auto nativeDevice = device->as<D3D12Device>();
    return core::createScope<D3D12DescriptorHeap>(count, type, nativeDevice, shaderVisible);
}


D3D12DescriptorHeap::D3D12DescriptorHeap(core::u32 count, DescriptorType type, D3D12Device* device, bool shaderVisible)
    : mDescriptorCount(count) {
    
    auto descType = getType(type);
    
    D3D12_DESCRIPTOR_HEAP_DESC dhd = {};
    dhd.NumDescriptors = count;
    dhd.Type = descType;

    if (!shaderVisible) {
        dhd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    }
    else {
        dhd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    }
    auto rawDevice = device->getDevice();

    HRESULT hres = rawDevice->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(&mDescriptorHeap));
    throwOnFailure(hres, "Failed to create ID3D12DescriptorHeap");

    mDescriptorSize = rawDevice->GetDescriptorHandleIncrementSize(descType);
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::getGPUHandle() const {
    return mDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::getCPUHandle() const {
    return mDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
}

core::u32 D3D12DescriptorHeap::getSize() const {
    return mDescriptorSize;
}

D3D12_DESCRIPTOR_HEAP_TYPE D3D12DescriptorHeap::getType(DescriptorType type) {
    switch (type) {
    case DescriptorType::RTV:
        return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        
    case DescriptorType::DSV:
        return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    }
    throw std::runtime_error("Unknown Descriptor type!");
}

}