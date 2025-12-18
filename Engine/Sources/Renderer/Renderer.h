#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <array>

namespace wrl = Microsoft::WRL;

namespace Mira {

class Renderer {
public:
	Renderer();
	~Renderer();

	void init(HWND handle);
	void shutdown();
	void wipeOff();
	void flipBuffers();


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
	std::array <float, 4>                 m_clearColor;

	//References
	HWND                                  p_handle;
};

}