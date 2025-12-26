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


private:
	Material* m_material = nullptr;
	Mesh*	  m_mesh = nullptr;
	ConstantBuffer* m_cbo = nullptr;
	Transform* m_transform = nullptr;
	Camera* p_camera = nullptr;
};

}