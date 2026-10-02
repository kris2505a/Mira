#include "mi_d3d12_device.hpp"
#include "mi_d3d12_helper.hpp"
#include <helpers/mi_types.hpp>

#include "mi_d3d12_command_list.hpp"

namespace mira::rhw {

D3D12Device::D3D12Device() {
    setupDebug();
    createFactory();
    createDevice();
    createCommandQueue();
}

void D3D12Device::setupDebug() {
#ifndef _DEBUG 
    return;
#endif
    core::Log::info("Setting up d3d12 debugger");
    HRESULT dbgHr = D3D12GetDebugInterface(IID_PPV_ARGS(&mDebug));
    throwOnFailure(dbgHr, "Failed to retrieve debug interface");
    mDebug->EnableDebugLayer();
}

void D3D12Device::createFactory() {
    core::Log::info("creating d3d12 factory");
    UINT factoryFlags = 0;

    #ifdef _DEBUG
        factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
    #endif

    HRESULT hres = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&mFactory));
    throwOnFailure(hres, "Failed to create factory");
}

void D3D12Device::createDevice() {
    core::Log::info("creating d3d12 device");
    HRESULT hres;
    core::ComScope<IDXGIAdapter1> adapter;

    for (core::u32 i = 0; mFactory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i) {
        DXGI_ADAPTER_DESC1 desc{};
        hres = adapter->GetDesc1(&desc);
        throwOnFailure(hres, "Failed to retrieve adapter");

        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            adapter->Release();
            continue;
        }
        core::Log::info("GPU: {}", core::toNarrow(desc.Description));
        break;
    }

    hres = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mDevice));
    throwOnFailure(hres, "Failed to create device");
}

void D3D12Device::createCommandQueue() {
    core::Log::info("creating d3d12 command queue");
    D3D12_COMMAND_QUEUE_DESC qd = {};
    qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    qd.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    qd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    qd.NodeMask = 0;

    HRESULT hres = mDevice->CreateCommandQueue(&qd, IID_PPV_ARGS(&mCmdQueue));
    throwOnFailure(hres, "Failed to create command queue");
}

core::Scope<IDevice> IDevice::create() {
    core::Log::info("creating mira::rhw::IDevice");
    return core::createScope<D3D12Device>();
}

ID3D12Device* D3D12Device::getDevice() const {
    return mDevice.Get();
}

ID3D12CommandQueue* D3D12Device::getCommandQueue() const {
    return mCmdQueue.Get();
}

IDXGIFactory6* D3D12Device::getFactory() const {
    return mFactory.Get();
}

void D3D12Device::executeCommands(ICommandList* cmdList) {
    auto rawCmdList = cmdList->as<D3D12CommandList>()->getList();

    ID3D12CommandList* lists[] = {
        rawCmdList
    };

    mCmdQueue->ExecuteCommandLists(1, lists);
}



}