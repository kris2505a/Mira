#pragma once
#include "Mira/Renderer/RHI/RHI.hpp"
#include <array>
#include <wrl/client.h>
#include <d3d11.h>

namespace Mira {

class D3D11RHI : public RHI {
public:
    D3D11RHI() = default;
    ~D3D11RHI() override = default;

    void initialize(WindowHandle handle, int width, int height) override;
    void shutdown()                     override;
    void bindRenderTarget()             override;
    void bindRasterizer()               override;
    void bindDepthStencil()             override;
    void setViewPort()                  override;
    void setTopology()                  override;
    void clear()                        override;
    void swap()                         override;
    void drawIndexed(uint32_t indices)  override;
    void resize(unsigned int width, unsigned int height)  override;
    void logGPUInfo()                   override;

    void clearColor(float r, float g, float b, float a) override;
    void setWireFrameMode(bool cond)    override;
    void setupImGui()                   override;
    void beginImGuiFrame()              override;
    void endImGuiFrame()                override;
    void shutDownImGui()                override;


private:
    void createDeviceSwapChain();
    void createRenderTargetView();
    void createViewPort();
    void createDepthStencilState();
    void createDepthStencilView();
    void createRasterizerState();
    void createSamplerState();

private:
    HWND p_handle															= nullptr;
    Microsoft::WRL::ComPtr <ID3D11Device>			 m_device				= nullptr;
    Microsoft::WRL::ComPtr <ID3D11DeviceContext>	 m_context				= nullptr;
    Microsoft::WRL::ComPtr <IDXGISwapChain>			 m_swapChain			= nullptr;
    Microsoft::WRL::ComPtr <ID3D11RenderTargetView>	 m_targetView			= nullptr;
    Microsoft::WRL::ComPtr <ID3D11DepthStencilView>	 m_stencilView			= nullptr;
    Microsoft::WRL::ComPtr <ID3D11DepthStencilState> m_stencilState			= nullptr;
    Microsoft::WRL::ComPtr <ID3D11RasterizerState>	 m_rasterizerSolid		= nullptr;
    Microsoft::WRL::ComPtr <ID3D11RasterizerState>	 m_rasterizerWireFrame	= nullptr;
    Microsoft::WRL::ComPtr <ID3D11SamplerState>		 m_samplerState			= nullptr;
    D3D11_VIEWPORT									 m_viewPort				= {};
    std::array <float, 4>							 m_clearColor			= { 0.0f, 0.0f, 0.0f, 1.0f };
    UINT											 m_renderWidth			= 0;
    UINT											 m_renderHeight			= 0;
    bool											 m_wireFrame			= false;
};

}