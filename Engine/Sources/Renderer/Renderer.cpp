#include <PreCompHeader.h>
#include "Renderer.h"
#include "Error.h"
#include "Logger/Log.h"

namespace Mira {

Renderer* Renderer::s_instance = nullptr;

Renderer::Renderer(WindowAttributes& attrib)
	: p_handle(nullptr), r_attrib(attrib) {

	m_clearColor      = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_viewPort        = {};
	m_renderWidth     = 0;
	m_renderHeight    = 0;
	m_initialized     = false;

	MIRA_ASSERT(!s_instance, "Renderer Instance Already Exists");
	s_instance = this;
}

void Renderer::init(HWND handle) {
	p_handle = handle;
	MIRA_LOG(LOG_INFO, "Renderer Initialized");
	this->createDeviceSwapChain();
	this->createRenderTargetView();
	this->createDepthStencilState();
	this->createDepthStencilView();
	this->createViewPort();

	this->bindEssentials();

	m_initialized = true;
}

void Renderer::createDeviceSwapChain() {
	DXGI_SWAP_CHAIN_DESC sd                 = {};
	sd.BufferDesc.Width                     = 0;
	sd.BufferDesc.Height                    = 0;
	sd.BufferDesc.RefreshRate.Numerator     = 0;
	sd.BufferDesc.RefreshRate.Denominator   = 0;
	sd.BufferDesc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering          = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	sd.BufferDesc.Scaling                   = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count                     = 1;
	sd.SampleDesc.Quality                   = 0;
	sd.BufferCount                          = 1;
	sd.OutputWindow                         = p_handle;
	sd.BufferUsage                          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Windowed                             = true;
	sd.SwapEffect                           = DXGI_SWAP_EFFECT_DISCARD;

	unsigned int debugFlags                 = 0;

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
	wrl::ComPtr<ID3D11Texture2D> pBackBuffer;
	HRUN(m_swapchain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)));

	D3D11_TEXTURE2D_DESC bbDesc;
	pBackBuffer->GetDesc(&bbDesc);

	m_renderWidth    = bbDesc.Width;
	m_renderHeight   = bbDesc.Height;
	HRUN(m_device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_targetView));
	
}


void Renderer::createViewPort() {
	m_viewPort.TopLeftX       = 0;
	m_viewPort.TopLeftY       = 0;
	m_viewPort.Width          = static_cast <float>(m_renderWidth);
	m_viewPort.Height         = static_cast <float>(m_renderHeight);
	m_viewPort.MinDepth		  = 0.0f;
	m_viewPort.MaxDepth		  = 1.0f;
}

void Renderer::createDepthStencilState() {

	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable				 = TRUE;
	dsd.DepthWriteMask			 = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc				 = D3D11_COMPARISON_LESS;
	dsd.StencilEnable			 = FALSE;

	HRUN(m_device->CreateDepthStencilState(&dsd, &m_stencilState));

}

void Renderer::createDepthStencilView() {


	D3D11_TEXTURE2D_DESC td = {};
	td.Width                = m_renderWidth;
	td.Height               = m_renderHeight;
	td.MipLevels            = 1;
	td.ArraySize			= 1;
	td.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Quality   = 0;
	td.SampleDesc.Count		= 1;
	td.Usage				= D3D11_USAGE_DEFAULT;
	td.BindFlags			= D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags		= 0;
	td.MiscFlags			= 0;

	wrl::ComPtr <ID3D11Texture2D> depthTexture;
	HRUN(m_device->CreateTexture2D(&td, nullptr, &depthTexture));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format						   = td.Format;
	dsvd.ViewDimension				   = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice			   = 0;

	HRUN(m_device->CreateDepthStencilView(depthTexture.Get(), &dsvd, &m_stencilView));
	
}

void Renderer::bindEssentials() {
	ID3D11RenderTargetView* rtvs[] = { m_targetView.Get() };

	RUN(m_context->OMSetRenderTargets(1, rtvs, m_stencilView.Get()), m_device);
	RUN(m_context->OMSetDepthStencilState(m_stencilState.Get(), 0), m_device);
	RUN(m_context->RSSetViewports(1, &m_viewPort), m_device);
	RUN(m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST), m_device);
}

void Renderer::wipeOff() {
	RUN(m_context->ClearRenderTargetView(m_targetView.Get(), m_clearColor.data()), m_device);
	RUN(m_context->ClearDepthStencilView(m_stencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0), m_device);
}

void Renderer::flipBuffers() {
	RUN(m_swapchain->Present(r_attrib.vSync, 0), m_device);
}

void Renderer::resizeCall() {
	MIRA_LOG(LOG_DEBUG, "Window Resize Call");

	ID3D11RenderTargetView* nullRTV = nullptr;
	m_context->OMSetRenderTargets(1, &nullRTV, nullptr);

	m_targetView.Reset();
	m_stencilView.Reset();
	
	HRUN(m_swapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));
	createRenderTargetView();
	createDepthStencilView();
	createViewPort();
	bindEssentials();
}

bool Renderer::isInitialized() const {
	return m_initialized;
}

void Renderer::shutdown() {
	m_initialized = false;
	MIRA_LOG(LOG_INFO, "Renderer Shutdown");
}

ID3D11Device* Renderer::device() const {
	return m_device.Get();
}

ID3D11DeviceContext* Renderer::context() const {
	return m_context.Get();
}

Renderer::~Renderer() {
	if (m_initialized)
		shutdown();
}

}