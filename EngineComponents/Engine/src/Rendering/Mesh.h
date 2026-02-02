#pragma once
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <memory>

namespace Mira {

class Mesh {
	friend class MeshInstanceData;
public:
	static std::unique_ptr <Mesh> quadMesh();

private:
	std::weak_ptr <MeshInstanceData> p_sharedInstanceData;
};

class MeshInstanceData {
public:
	std::unique_ptr <dxr::VertexBuffer> m_vbo;
	std::unique_ptr <dxr::IndexBuffer> m_ibo;
	static std::shared_ptr <MeshInstanceData> s_quadInstance;
};

}