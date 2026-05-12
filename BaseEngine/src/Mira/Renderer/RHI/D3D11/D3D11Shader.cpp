#include "MiraPch.h"
#include "D3D11Shader.h"
#include "D3DError.h"
#include "Mira/Logger/Logger.h"
#include "D3D11Resource.h"

namespace Mira {

D3D11Shader::D3D11Shader(const std::wstring& name, InputLayout layout) {

    //Loading of precompiled shader
    std::wstring vsPath = L"shader/" + name + L"VS.cso";
    std::wstring psPath = L"shader/" + name + L"PS.cso";

    HRUN(D3DReadFileToBlob(vsPath.c_str(), m_vsBlob.GetAddressOf()));
    HRUN(D3DReadFileToBlob(psPath.c_str(), m_psBlob.GetAddressOf()));

    /* 

    //MANUAL COMPILATION OF SHADER VIA ENGINE
    
    std::wstring vsPath = L"shader/" + name + L"VS.hlsl";
    std::wstring psPath = L"shader/" + name + L"PS.hlsl";

    Microsoft::WRL::ComPtr<ID3DBlob> vsErrBlob, psErrBlob;

    auto vsHr = D3DCompileFromFile(
        vsPath.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "vs_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        m_vsBlob.GetAddressOf(),
        vsErrBlob.GetAddressOf()
    );

    if (FAILED(vsHr)) {
        if (vsErrBlob) {
            Logger::log(LogType::Error, "Failed to compile vertex shader: {}", std::string((char*)vsErrBlob->GetBufferPointer()));
        }
    }

    auto psHr = D3DCompileFromFile(
        psPath.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "ps_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        m_psBlob.GetAddressOf(),
        psErrBlob.GetAddressOf()
    );

    if (FAILED(psHr)) {
        if (psErrBlob) {
            Logger::log(LogType::Error, "Failed to compile pixelShader shader: {}", std::string((char*)psErrBlob->GetBufferPointer()));
        }
    }
    */

    HRUN(D3D11Resource::getDevice()->CreateVertexShader(
        m_vsBlob->GetBufferPointer(),
        m_vsBlob->GetBufferSize(),
        nullptr,
        m_vertexShader.GetAddressOf()
    ));
    HRUN(D3D11Resource::getDevice()->CreatePixelShader(
        m_psBlob->GetBufferPointer(),
        m_psBlob->GetBufferSize(),
        nullptr,
        m_pixelShader.GetAddressOf()
    ));

    // Creation of input layout
    for (uint32_t i = 0; i < layout.getLayouts().size(); i++) {
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
        const auto& l = layout.getLayouts()[i];

        if (l.type == LayoutDataType::Float) {
            switch (l.count) {
            case 1:
                format = DXGI_FORMAT_R32_FLOAT;
                break;

            case 2:
                format = DXGI_FORMAT_R32G32_FLOAT;
                break;

            case 3:
                format = DXGI_FORMAT_R32G32B32_FLOAT;
                break;

            case 4:
                format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                break;

            default:
                format = DXGI_FORMAT_UNKNOWN;
                break;
            }
        }

        m_layoutDesc.push_back(
            {
                l.semanticName.c_str(),
                0,
                format,
                0,
                i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT,
                D3D11_INPUT_PER_VERTEX_DATA,
                0
            }
        );
    }

    HRUN(D3D11Resource::getDevice()->CreateInputLayout(
        m_layoutDesc.data(),
        m_layoutDesc.size(),
        m_vsBlob->GetBufferPointer(),
        m_vsBlob->GetBufferSize(),
        m_inputLayout.GetAddressOf()
    ));

}

void D3D11Shader::bind() const {
    RUN(D3D11Resource::getContext()->VSSetShader(m_vertexShader.Get(), nullptr, 0), D3D11Resource::getDevice());
    RUN(D3D11Resource::getContext()->PSSetShader(m_pixelShader.Get(), nullptr, 0), D3D11Resource::getDevice());
    RUN(D3D11Resource::getContext()->IASetInputLayout(m_inputLayout.Get()), D3D11Resource::getDevice());
}

}