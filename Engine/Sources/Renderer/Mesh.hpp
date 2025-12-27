#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Mira {

class Mesh {
public:
	Mesh() = default;
	~Mesh();
	
	static Mesh* cubeMesh();

	uint32_t indexCount() const;
	

private:
	VertexBuffer* m_vbo;
	IndexBuffer*  m_ibo;

};

}