#pragma once
#include <WRL/client.h>
#include <d3d11.h>
#include <array>
#include "Entity/Entity.hpp"
#include "ConstantBuffer.hpp"
#include "Components/Camera.hpp"

namespace wrl = Microsoft::WRL;

class Renderer {
    friend class BindsBase;
    friend class Entity;

public:
    Renderer(HWND handle);
    ~Renderer();
    void preRender();
    void drawIndexed(unsigned int count);
    void renderEntity(const Entity* entity);
    void postRender();
    void setActiveCamera(Camera* camera);

private:
	void createDeviceSwapChain();
	void createRenderTargetView();
	void createViewPort();
	void createDepthStencilState();
	void createDepthStencilView();
    void createRasterizerState();
    void createSamplerState();
    void clear();
    void swap();

private:
    wrl::ComPtr <ID3D11Device> m_device;
    wrl::ComPtr <ID3D11DeviceContext> m_context;
    wrl::ComPtr <IDXGISwapChain> m_swapchain;
    wrl::ComPtr <ID3D11RenderTargetView> m_targetView;
	wrl::ComPtr <ID3D11DepthStencilView> m_stencilView;
	wrl::ComPtr <ID3D11DepthStencilState> m_stencilState;
    wrl::ComPtr <ID3D11RasterizerState> m_rasterizerState;
    wrl::ComPtr <ID3D11SamplerState> m_samplerState;
	std::array <float, 4> m_clearColor;

	D3D11_VIEWPORT m_viewPort;

    int m_renderWidth;
    int m_renderHeight;

    HWND p_handle;

    std::unique_ptr <ConstantBuffer> m_vertexCBO;
    std::unique_ptr <ConstantBuffer> m_pixelCBO;

    Camera* p_activeCamera;
    Camera m_defaultCamera;

    static Renderer* s_instance;
};