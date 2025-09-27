#pragma once
#include <d3d11.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

namespace Mira {

class Renderer {
public:
	Renderer(HWND handle);
	~Renderer() = default;

	void wipeScreen(float r, float g, float b, float a);
	void swapBuffers();

private:
	void createDeviceAndSwapChain(HWND handle);
	void createTargetView();
	void setViewPort();

private:
	wrl::ComPtr <ID3D11Device> m_device;
	wrl::ComPtr <ID3D11DeviceContext> m_context;
	wrl::ComPtr <IDXGISwapChain> m_swapChain;
	wrl::ComPtr <ID3D11RenderTargetView> m_targetView;

};

}