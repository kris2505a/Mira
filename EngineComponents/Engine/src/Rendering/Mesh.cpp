#include "Mesh.h"
#include <Vertex2.h>
#include <vector>

namespace Mira {

std::shared_ptr <MeshInstanceData> MeshInstanceData::s_quadInstance = nullptr;

std::unique_ptr<Mesh> Mesh::quadMesh() {
	auto mesh = std::make_unique <Mesh>();
	if (MeshInstanceData::s_quadInstance) {
		mesh->p_sharedInstanceData = MeshInstanceData::s_quadInstance;
		return mesh;
	}

	MeshInstanceData::s_quadInstance = std::make_shared<MeshInstanceData>();

	std::vector <dxr::Vertex2> vertices = {
		// position            normal         uv
		{ {-0.5f, -0.5f},     {0.0f, 1.0f},   {0.0f, 1.0f} }, // 0 bottom-left
		{ { 0.5f, -0.5f},     {0.0f, 1.0f},   {1.0f, 1.0f} }, // 1 bottom-right
		{ { 0.5f,  0.5f},     {0.0f, 1.0f},   {1.0f, 0.0f} }, // 2 top-right
		{ {-0.5f,  0.5f},     {0.0f, 1.0f},   {0.0f, 0.0f} }, // 3 top-left
	};

	MeshInstanceData::s_quadInstance->m_vbo = std::make_unique <dxr::VertexBuffer>(
		vertices.data(),
		static_cast <unsigned int> (vertices.size()),
		sizeof(dxr::Vertex2)
	);

	std::vector <uint32_t> indices{
		0, 1, 2,
		2, 3, 0
	};

	MeshInstanceData::s_quadInstance->m_ibo = std::make_unique <dxr::IndexBuffer>(
		indices.data(),
		static_cast <unsigned int> (indices.size())
	);

	mesh->p_sharedInstanceData = MeshInstanceData::s_quadInstance;
	return mesh;	
}

}