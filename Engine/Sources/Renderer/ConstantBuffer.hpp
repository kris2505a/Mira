#pragma once
#include "Binds.hpp"
#include "ShaderType.hpp"

namespace Mira {

class ConstantBuffer : public Binds {
public:
	ConstantBuffer(const void* data, size_t size, ShaderType type);
	~ConstantBuffer() = default;
	void bind() const final override;
	void update(const void* data, size_t size);

private:
	wrl::ComPtr <ID3D11Buffer> m_buffer;
	ShaderType m_type;
};

}