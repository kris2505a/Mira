#include "MiraPch.hpp"
#include "D3D11IndexBuffer.hpp"
#include "D3D11Resource.hpp"
#include "D3DError.hpp"

namespace Mira {

D3D11IndexBuffer::D3D11IndexBuffer(const void* indices, int count, int offset)
    :   m_count(static_cast <UINT>(count)), m_offset(static_cast <UINT>(offset)) {

    D3D11_BUFFER_DESC bd	= {};
    bd.Usage				= D3D11_USAGE_DEFAULT;
    bd.BindFlags			= D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags		= 0;
    bd.MiscFlags			= 0;
    bd.ByteWidth			= count * sizeof(uint32_t);
    bd.StructureByteStride	= sizeof(uint32_t);

    D3D11_SUBRESOURCE_DATA srd	= {};
    srd.pSysMem					= indices;

    HRUN(D3D11Resource::getDevice()->CreateBuffer(&bd, &srd, &m_buffer));

}

void D3D11IndexBuffer::bind() const {
    RUN(D3D11Resource::getContext()->IASetIndexBuffer(m_buffer.Get(), DXGI_FORMAT_R32_UINT, m_offset), D3D11Resource::getDevice());
}

unsigned int D3D11IndexBuffer::getCount() const {
    return m_count;
}

}
