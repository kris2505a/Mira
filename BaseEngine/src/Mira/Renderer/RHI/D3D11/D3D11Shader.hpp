#pragma once
#include "Mira/Renderer/RHI/Shader.hpp"
#include <wrl/client.h>
#include <d3d11.h>

namespace Mira {

class D3D11Shader : public Shader {
public:
    D3D11Shader(const std::wstring& name, InputLayout layout);
    ~D3D11Shader() override = default;
    void bind() const override;

private:
    Microsoft::WRL::ComPtr <ID3D11VertexShader> m_vertexShader  = nullptr;
    Microsoft::WRL::ComPtr <ID3D11PixelShader> m_pixelShader	= nullptr;

    Microsoft::WRL::ComPtr <ID3DBlob> m_vsBlob					= nullptr;
    Microsoft::WRL::ComPtr <ID3DBlob> m_psBlob					= nullptr;

    Microsoft::WRL::ComPtr <ID3D11InputLayout> m_inputLayout	= nullptr;

    std::vector <D3D11_INPUT_ELEMENT_DESC> m_layoutDesc			= {};
};

}