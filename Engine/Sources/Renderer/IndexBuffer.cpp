#include <PreCompHeader.hpp>
#include "IndexBuffer.hpp"
#include "Error.hpp"

namespace Mira {

IndexBuffer::IndexBuffer(const void* data, size_t size, size_t count, UINT offset)
	: m_offset(offset), m_indexCount(count) {
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.ByteWidth = size;
	bd.StructureByteStride = sizeof(uint32_t);

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = data;

	HRUN(device()->CreateBuffer(&bd, &srd, &m_buffer));
}

void IndexBuffer::bind() const {
	RUN(context()->IASetIndexBuffer(m_buffer.Get(), DXGI_FORMAT_R32_UINT, m_offset), device());
}

size_t IndexBuffer::indexCount() const {
	return m_indexCount;
}

}