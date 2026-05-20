#pragma once
#include "Mira/Renderer/RHI/IndexBuffer.hpp"
#include <wrl/client.h>
#include <d3d11.h>

namespace Mira {

class D3D11IndexBuffer : public IndexBuffer {
public:
    D3D11IndexBuffer(const void* indices, int count, int offset);
    ~D3D11IndexBuffer() override = default;
    void bind()				const override;
    [[nodiscard]] unsigned int getCount() const override;

private:
    Microsoft::WRL::ComPtr <ID3D11Buffer>	m_buffer	= nullptr;
    UINT									m_count		= 0;
    UINT									m_offset	= 0;
};

}