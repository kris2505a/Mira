#include "MiraPch.h"
#include "D3D11ConstantBuffer.h"
#include "D3DError.h"
#include "D3D11Resource.h"

namespace Mira {

D3D11ConstantBuffer::D3D11ConstantBuffer(const void* data, int size, ShaderType type, int slot) {
    m_slot		= slot;
    m_type		= type;

    D3D11_BUFFER_DESC bd	= {};
    bd.Usage				= D3D11_USAGE_DYNAMIC;
    bd.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
    bd.MiscFlags			= 0;
    bd.ByteWidth			= (size + 15) & ~15;
    bd.StructureByteStride	= 0;

    D3D11_SUBRESOURCE_DATA srd = {};
    srd.pSysMem = data;

    HRUN(D3D11Resource::getDevice()->CreateBuffer(&bd, &srd, &m_buffer));
}

void D3D11ConstantBuffer::bind() const {
    switch (m_type) {
    case ShaderType::VertexShader:
        RUN(D3D11Resource::getContext()->VSSetConstantBuffers(
            static_cast <UINT>(m_slot),
            1,
            m_buffer.GetAddressOf()),
            D3D11Resource::getDevice()
        );
        break;

    case ShaderType::PixelShader:
        RUN(D3D11Resource::getContext()->PSSetConstantBuffers(
            static_cast <UINT>(m_slot),
            1,
            m_buffer.GetAddressOf()),
            D3D11Resource::getDevice()
        );
        break;

    default:
        break;
    }
}

void D3D11ConstantBuffer::update(const void* data, int size) {
    auto roundedSize = (size + 15) & ~15;

    D3D11_MAPPED_SUBRESOURCE map;
    RUN(D3D11Resource::getContext()->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map), D3D11Resource::getDevice());
    memcpy(map.pData, data, roundedSize);
    RUN(D3D11Resource::getContext()->Unmap(m_buffer.Get(), 0), D3D11Resource::getDevice());
}

}