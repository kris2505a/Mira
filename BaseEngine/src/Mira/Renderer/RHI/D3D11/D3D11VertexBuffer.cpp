#include "MiraPch.hpp"
#include "D3D11VertexBuffer.hpp"
#include "D3DError.hpp"
#include "D3D11Resource.hpp"

namespace Mira {

D3D11VertexBuffer::D3D11VertexBuffer(const void* data, int count, int stride, int offset)
    : m_stride(static_cast<UINT>(stride)), m_offset(static_cast<UINT>(offset)) {

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.ByteWidth = m_stride * count;
    bd.StructureByteStride = m_stride;

    D3D11_SUBRESOURCE_DATA srd = {};
    srd.pSysMem = data;

    HRUN(D3D11Resource::getDevice()->CreateBuffer(&bd, &srd, &m_buffer));

}

void D3D11VertexBuffer::bind() const {
    RUN(D3D11Resource::getContext()->IASetVertexBuffers(0, 1, m_buffer.GetAddressOf(), &m_stride, &m_offset), D3D11Resource::getDevice());
}

}