#include "Renderer.h"
#include "Error.h"
#include "Logger/Log.h"

namespace Mira {

Renderer::Renderer()
	: p_handle(nullptr) {

	m_clearColor = { 0.0f, 0.0f, 0.0f, 0.0f };
}

void Renderer::init(HWND handle) {
	p_handle = handle;
	MIRA_LOG(LOG_INFO, "Renderer Initialized");
	this->createDeviceSwapChain();
	this->createRenderTargetView();
}

void Renderer::createDeviceSwapChain() {
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferCount = 1;
	sd.OutputWindow = p_handle;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

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
		&m_swapchain,
		&m_device,
		nullptr,
		&m_context
	));
}

void Renderer::createRenderTargetView() {
	wrl::ComPtr <ID3D11Resource> pBackBuffer;
	HRUN(m_swapchain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	HRUN(m_device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_targetView));
}

void Renderer::createViewPort() {
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 1920.0f;
	vp.Height = 1080.0f;
}

void Renderer::wipeOff() {
	RUN(m_context->ClearRenderTargetView(m_targetView.Get(), m_clearColor.data()), m_device.Get());
}

void Renderer::flipBuffers() {
	RUN(m_swapchain->Present(0, 0), m_device.Get());
}

void Renderer::shutdown() {
	MIRA_LOG(LOG_INFO, "Renderer Shutdown");
}

Renderer::~Renderer() {

}

}