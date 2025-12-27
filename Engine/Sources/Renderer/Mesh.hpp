#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Core/Core.hpp"

namespace Mira {

class MIRA_API Mesh {
public:
	Mesh() = default;
	~Mesh();
	static Mesh* cubeMesh();
	uint32_t indexCount() const;
	
	void bind() {
		m_vbo->bind();
		m_ibo->bind();
	}

private:
	VertexBuffer* m_vbo;
	IndexBuffer*  m_ibo;

};

}