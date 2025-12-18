#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <array>
#include "Core/WindowAttributes.h"

namespace wrl = Microsoft::WRL;

namespace Mira {

class Renderer {
public:
	Renderer(WindowAttributes& attrib);
	~Renderer();

	void init(HWND handle);
	void shutdown();
	void wipeOff();
	void flipBuffers();
	void bindEssentials();

private:
	void createDeviceSwapChain();
	void createRenderTargetView();
	void createViewPort();
	void createDepthStencil();

private:

	//Members
	wrl::ComPtr <ID3D11Device>            m_device;
	wrl::ComPtr <ID3D11DeviceContext>     m_context;
	wrl::ComPtr <IDXGISwapChain>          m_swapchain;
	wrl::ComPtr <ID3D11RenderTargetView>  m_targetView;
	wrl::ComPtr <ID3D11DepthStencilView>  m_stencilView;
	wrl::ComPtr <ID3D11DepthStencilState> m_stencilState;

	std::array <float, 4>                 m_clearColor;

	D3D11_VIEWPORT						  m_viewPort;
	
	int									  m_renderWidth;
	int									  m_renderHeight;

	//References
	HWND                                  p_handle;
	WindowAttributes&					  r_attrib;

};

}