#pragma once
#include "Mira/Renderer/RHI/VertexBuffer.hpp"
#include <wrl/client.h>
#include <d3d11.h>

namespace Mira {

class D3D11VertexBuffer : public VertexBuffer {
public:
    D3D11VertexBuffer(const void* data, int count, int stride, int offset);
    ~D3D11VertexBuffer() override = default;
    void bind() const override;

private:
    Microsoft::WRL::ComPtr <ID3D11Buffer>	m_buffer	= nullptr;
    UINT									m_stride	= 0;
    UINT									m_offset	= 0;
};

}