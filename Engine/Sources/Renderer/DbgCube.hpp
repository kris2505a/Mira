#pragma once
#include "Core/Core.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Math/Vertex.hpp"
#include "ConstantBuffer.hpp"
#include "Components/Transform.hpp"
#include "Components/Camera.hpp"

namespace Mira {

namespace dx = DirectX;

class MIRA_API DbgCube {
public:
	DbgCube(Material* material, Mesh* mesh, Camera* camera);
	~DbgCube();
	void pulse(float deltaTime);
	void render();
	Transform* transform();
	void color(float r, float g, float b) {
		m_color = { r, g, b, 1.0f };
	}


private:
	Material* m_material = nullptr;
	Mesh*	  m_mesh = nullptr;
	ConstantBuffer* m_cbo = nullptr;
	ConstantBuffer* m_ccbo = nullptr;
	Transform* m_transform = nullptr;
	Camera* p_camera = nullptr;
	dx::XMFLOAT4 m_color;

};

}