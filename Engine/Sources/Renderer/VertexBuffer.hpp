#pragma once
#include "Binds.hpp"

namespace Mira {

class VertexBuffer : public Binds {
public:
	VertexBuffer(const void* vertices, size_t size, UINT stride, UINT offset = 0);
	~VertexBuffer() = default;
	void bind() const final override;

private:
	wrl::ComPtr <ID3D11Buffer> m_buffer;
	UINT m_stride;
	UINT m_offset;
};

}