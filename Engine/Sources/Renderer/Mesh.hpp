#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Mira {

class Mesh {
public:
	Mesh() = default;
	~Mesh();
	
	static Mesh* cubeMesh();

	void bind() {
		m_vbo->bind();
		m_ibo->bind();
	}

private:
	VertexBuffer* m_vbo;
	IndexBuffer*  m_ibo;

};

}