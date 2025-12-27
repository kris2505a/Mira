#pragma once
#include "binds.hpp"

namespace Mira {

class IndexBuffer : public Binds {
public:
	IndexBuffer(const void* data, size_t size, size_t count,UINT offset = 0);
	~IndexBuffer() = default;

	void bind() const final override;
	uint32_t indexCount() const;

private:
	wrl::ComPtr <ID3D11Buffer> m_buffer;
	UINT m_offset;
	size_t m_indexCount;
};

}