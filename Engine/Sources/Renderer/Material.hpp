#pragma once
#include "Shader.hpp"
#include "InputLayout.hpp"
#include "ConstantBuffer.hpp"
#include <DirectXMath.h>

namespace Mira {

class Material {
public:
	Material() = default;
	~Material();

	static Material* createMaterial();

	void bind() {
		m_shader->bind();
		m_layout->bind();
	}

	void color(const DirectX::XMFLOAT4& color);

private:
	InputLayout* m_layout;
	Shader* m_shader;
	ConstantBuffer* m_pcbo;
	DirectX::XMFLOAT4 m_defaultColor;
};

}