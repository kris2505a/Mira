#include <MiraPreCompHeader.h>
#include "Renderer.h"

namespace Mira {

//PUBLIC FUNCTIONS
Renderer::Renderer(HWND handle)
	: m_device(nullptr), m_context(nullptr), m_swapChain(nullptr) {

	this->createDeviceAndSwapChain(handle);
	this->createTargetView();
	this->setViewPort();
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer::wipeScreen(float r, float g, float b, float a) {
	float color[] = { r, g, b, a };
	m_context->ClearRenderTargetView(m_targetView.Get(), color);
}

void Renderer::swapBuffers() {
	m_swapChain->Present(0, 0);
}

//PRIVATE FUNCTIONS
void Renderer::createDeviceAndSwapChain(HWND handle) {
	DXGI_SWAP_CHAIN_DESC sDesc = {};

	sDesc.BufferDesc.Width = 0;
	sDesc.BufferDesc.Height = 0;
	sDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sDesc.BufferDesc.RefreshRate.Numerator = 0;
	sDesc.BufferDesc.RefreshRate.Denominator = 0;
	sDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sDesc.SampleDesc.Count = 1;
	sDesc.SampleDesc.Quality = 0;
	sDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sDesc.Windowed = TRUE;
	sDesc.BufferCount = 1;
	sDesc.OutputWindow = handle;
	sDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sDesc.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sDesc,
		&m_swapChain,
		&m_device,
		nullptr,
		&m_context
	);
}

void Renderer::createTargetView() {
	wrl::ComPtr <ID3D11Resource> p_backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &p_backBuffer);
	m_device->CreateRenderTargetView(p_backBuffer.Get(), nullptr, &m_targetView);
}

void Renderer::setViewPort() {
	D3D11_VIEWPORT vp;
	vp.Width = 1600.f;
	vp.Height = 900.f;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_context->RSSetViewports(1, &vp);
}

}