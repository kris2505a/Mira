#pragma once
#include "Core/Core.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Math/Vertex.hpp"
#include "ConstantBuffer.hpp"

namespace Mira {

namespace dx = DirectX;

class MIRA_API DbgCube {
public:
	DbgCube(Material* material, Mesh* mesh)
		: m_material(material), m_mesh(mesh){

		dx::XMMATRIX mat = dx::XMMatrixTranspose(
			dx::XMMatrixRotationZ(dx::XMConvertToRadians(30.0f)) *
			dx::XMMatrixScaling(9.0f / 16.0f, 1.0f, 1.0f)
		);
		
		m_cbo = new ConstantBuffer(&mat, sizeof(mat), ShaderType::VertexShader);

	}

	~DbgCube() {
		if (m_cbo)
			delete m_cbo;
	}
	
	void bind() {
		m_mesh->bind();
		m_material->bind();
		m_cbo->bind();
	}

private:
	Material* m_material = nullptr;
	Mesh*	  m_mesh = nullptr;
	ConstantBuffer* m_cbo = nullptr;
};

}