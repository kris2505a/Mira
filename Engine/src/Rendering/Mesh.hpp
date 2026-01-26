#pragma once
#include "Rendering/VertexBuffer.hpp"
#include "Rendering/IndexBuffer.hpp"
#include <memory>
#include <string>

class Mesh {
	friend class Renderer;
public:
	Mesh() = default;
	~Mesh() = default;
	
	void bind();
	unsigned int getIndexCount() const;
	
	static std::unique_ptr <Mesh> createCubeMesh();
	static std::unique_ptr <Mesh> createCustomMesh(const std::string& path);

private:
	std::weak_ptr <class MeshSharedState> m_sharedState;
};

class MeshSharedState {
	friend class Mesh;
private:
	std::unique_ptr <VertexBuffer> m_vbo;
	std::unique_ptr <IndexBuffer> m_ibo;

	static std::shared_ptr <MeshSharedState> s_cubeMesh;
};