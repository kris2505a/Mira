#pragma once
#include "Shader.hpp"
#include "InputLayout.hpp"

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

private:
	InputLayout* m_layout;
	Shader* m_shader;
};

}