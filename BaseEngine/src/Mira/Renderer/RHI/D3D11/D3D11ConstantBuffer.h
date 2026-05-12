#pragma once
#include "Mira/Renderer/RHI/ConstantBuffer.h"
#include <d3d11.h>
#include <wrl/client.h>
#include "Mira/Renderer/RHI/ShaderType.h"

namespace Mira {

class D3D11ConstantBuffer : public ConstantBuffer {
public:
    D3D11ConstantBuffer(const void* data, int size, ShaderType type, int slot = 0);
    ~D3D11ConstantBuffer() override = default;
    void bind() const override;
    void update(const void* data, int size) override;

private:
    Microsoft::WRL::ComPtr <ID3D11Buffer> m_buffer	= nullptr;
    ShaderType m_type								= ShaderType::None;
    int m_slot										= 0;
};

}