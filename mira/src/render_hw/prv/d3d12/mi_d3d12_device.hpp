#pragma once

#include "pub/mi_device.hpp"

#include "helpers/mi_win_hpr.hpp"
#include <d3d12.h>
#include <dxgi1_6.h>

namespace mira::rhw {

class D3D12Device : public IDevice {
public:
    D3D12Device();
    ~D3D12Device() override = default;
    ID3D12Device* getDevice() const;
    ID3D12CommandQueue* getCommandQueue() const;
    IDXGIFactory6* getFactory() const;

private:
    void setupDebug();
    void createFactory();
    void createDevice();
    void createCommandQueue();

private:
    core::ComScope<IDXGIFactory6> mFactory;
    core::ComScope<ID3D12Device> mDevice;
    core::ComScope<ID3D12Debug> mDebug;
    core::ComScope<ID3D12CommandQueue> mCmdQueue;
};


}