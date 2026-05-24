#include "MiraPch.hpp"
#include "D3D11RHI.hpp"
#include "D3DError.hpp"
#include "Mira/Logger/Logger.hpp"

#include "D3D11Resource.hpp"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace Mira {
void D3D11RHI::initialize(WindowHandle handle, int width, int height) {

    Logger::log(LogType::Info, "Initializing D3D11RHI...");
    p_handle = handle.handle;
	m_renderWidth = width;
	m_renderHeight = height;
	createDeviceSwapChain();
    createRenderTargetView();
    createDepthStencilState();
    createDepthStencilView();
    createViewPort();
    createRasterizerState();
    createSamplerState();

}

void D3D11RHI::shutdown() {
    Logger::log(LogType::Info, "Shutting Down D3D11RHI...");
}

void D3D11RHI::setupImGui() {

	ImGui_ImplWin32_Init(p_handle);
	ImGui_ImplDX11_Init(m_device.Get(), m_context.Get());

}

void D3D11RHI::beginImGuiFrame() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
}

void D3D11RHI::endImGuiFrame() {
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void D3D11RHI::shutDownImGui() {
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
}

Vec2 D3D11RHI::getRenderDimensions() {
	return Vec2(static_cast<float>(m_renderWidth), static_cast<float>(m_renderHeight));
}

void D3D11RHI::bindRenderTarget() {
    RUN(m_context->OMSetRenderTargets(1, m_targetView.GetAddressOf(), m_stencilView.Get()), m_device);
}

void D3D11RHI::bindRasterizer() {
    if (m_wireFrame) {
        RUN(m_context->RSSetState(m_rasterizerWireFrame.Get()), m_device);
    }
    else {
        RUN(m_context->RSSetState(m_rasterizerSolid.Get()), m_device);
    }
}

void D3D11RHI::bindDepthStencil() {
    RUN(m_context->OMSetDepthStencilState(m_stencilState.Get(), 0), m_device);
}

void D3D11RHI::setViewPort() {
    RUN(m_context->RSSetViewports(1, &m_viewPort), m_device);
}

void D3D11RHI::setTopology() {
    RUN(m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST), m_device);
}

void D3D11RHI::clear() {
    RUN(m_context->ClearRenderTargetView(m_targetView.Get(), m_clearColor.data()), m_device);
    RUN(m_context->ClearDepthStencilView(m_stencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0), m_device);
}

void D3D11RHI::swap() {
    RUN(m_swapChain->Present(1, 0), m_device);
}

void D3D11RHI::resize(unsigned int width, unsigned int height) {

	if (width == 0 || height == 0) {
		return;
	}

	m_context->OMSetRenderTargets(0, nullptr, nullptr);

    //Reset stuff
    m_targetView.Reset();
    m_stencilView.Reset();
    m_stencilState.Reset();

    m_renderWidth = width;
    m_renderHeight = height;

    //Resize swap chain buffer
    m_swapChain->ResizeBuffers(
        0,
        width,
        height,
        DXGI_FORMAT_UNKNOWN,
        0
    );

    createRenderTargetView();
    createDepthStencilView();
    createDepthStencilState();
    createViewPort();

}

void D3D11RHI::drawIndexed(uint32_t indices) {
    m_context->DrawIndexed(indices, 0, 0);
}

void D3D11RHI::logGPUInfo() {
    IDXGIDevice* dxgiDevice = nullptr;
    HRUN(m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

    IDXGIAdapter* adapter = nullptr;
    dxgiDevice->GetAdapter(&adapter);
    DXGI_ADAPTER_DESC desc;
    adapter->GetDesc(&desc);

    auto name = std::wstring(desc.Description);

    Logger::log(LogType::Debug, "GPU: {}", std::string(name.begin(), name.end()));

    std::string vendor;

    switch (desc.VendorId) {
    case 0x10DE:
        vendor = "NVIDIA";
        break;

    case 0x1002:
        vendor = "AMD";
        break;

    case 0x8086:
        vendor = "Intel";
        break;

    default:
        vendor = "Unknown";
        break;
    }

    Logger::log(LogType::Debug, "Vendor: {}", vendor);
    Logger::log(LogType::Debug, "V-RAM: {}", (desc.DedicatedVideoMemory / (1024 * 1024)));

}

void D3D11RHI::clearColor(float r, float g, float b, float a) {
    m_clearColor = { r, g, b, a};
}

void D3D11RHI::setWireFrameMode(bool cond) {
    m_wireFrame = cond;
}


#pragma region Initializations

void D3D11RHI::createDeviceSwapChain() {
	DXGI_SWAP_CHAIN_DESC sd					= {};
	sd.BufferDesc.Width						= 0;
	sd.BufferDesc.Height					= 0;
	sd.BufferDesc.RefreshRate.Numerator		= 0;
	sd.BufferDesc.RefreshRate.Denominator	= 0;
	sd.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	sd.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count						= 1;
	sd.SampleDesc.Quality					= 0;
	sd.BufferCount							= 1;
	sd.OutputWindow							= p_handle;
	sd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Windowed								= true;
	sd.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;

	unsigned int debugFlags = 0;

#ifdef _DEBUG
	debugFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	HRUN(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		debugFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_context
	));

    D3D11Resource::setResource(m_device.Get(), m_context.Get());
}

void D3D11RHI::createRenderTargetView() {
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
	HRUN(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)));

	D3D11_TEXTURE2D_DESC bbDesc;
	pBackBuffer->GetDesc(&bbDesc);

	m_renderWidth	= bbDesc.Width;
	m_renderHeight	= bbDesc.Height;
	HRUN(m_device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_targetView));
}

void D3D11RHI::createViewPort() {
	m_viewPort.TopLeftX = 0;
	m_viewPort.TopLeftY = 0;
	m_viewPort.Width	= static_cast <float>(m_renderWidth);
	m_viewPort.Height	= static_cast <float>(m_renderHeight);
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;
}

void D3D11RHI::createDepthStencilState() {
	D3D11_DEPTH_STENCIL_DESC dsd	= {};
	dsd.DepthEnable					= TRUE;
	dsd.DepthWriteMask				= D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc					= D3D11_COMPARISON_LESS;
	dsd.StencilEnable				= FALSE;

	HRUN(m_device->CreateDepthStencilState(&dsd, &m_stencilState));
}

void D3D11RHI::createDepthStencilView() {
	D3D11_TEXTURE2D_DESC td = {};
	td.Width				= m_renderWidth;
	td.Height				= m_renderHeight;
	td.MipLevels			= 1;
	td.ArraySize			= 1;
	td.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Quality	= 0;
	td.SampleDesc.Count		= 1;
	td.Usage				= D3D11_USAGE_DEFAULT;
	td.BindFlags			= D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags		= 0;
	td.MiscFlags			= 0;

	Microsoft::WRL::ComPtr <ID3D11Texture2D> depthTexture;
	HRUN(m_device->CreateTexture2D(&td, nullptr, &depthTexture));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd	= {};
	dsvd.Format							= td.Format;
	dsvd.ViewDimension					= D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice				= 0;

	HRUN(m_device->CreateDepthStencilView(depthTexture.Get(), &dsvd, &m_stencilView));
}

void D3D11RHI::createRasterizerState() {
	D3D11_RASTERIZER_DESC rd	= {};
	rd.DepthClipEnable			= true;
	rd.FrontCounterClockwise	= true;
	rd.FillMode					= D3D11_FILL_SOLID;
	rd.CullMode					= D3D11_CULL_FRONT;

	HRUN(m_device->CreateRasterizerState(&rd, m_rasterizerSolid.GetAddressOf()));

	D3D11_RASTERIZER_DESC rdw	= {};
	rdw.DepthClipEnable			= true;
	rdw.FrontCounterClockwise	= true;
	rdw.FillMode				= D3D11_FILL_WIREFRAME;
	rdw.CullMode				= D3D11_CULL_FRONT;

	HRUN(m_device->CreateRasterizerState(&rdw, m_rasterizerWireFrame.GetAddressOf()));
}

void D3D11RHI::createSamplerState() {
	D3D11_SAMPLER_DESC sd	= {};
	sd.Filter				= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU				= D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV				= D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW				= D3D11_TEXTURE_ADDRESS_WRAP;

	HRUN(m_device->CreateSamplerState(&sd, m_samplerState.GetAddressOf()));
	RUN(m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf()), m_device);
}

#pragma endregion

}
