#pragma once
#include "Core/Core.hpp"
#include "Entity.hpp"
#include "Drawable.hpp"
#include "Components/RenderComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/Camera.hpp"

namespace Mira {

class MIRA_API Cube : public Entity, Drawable {
public:
	Cube() = default;
	~Cube() = default;

	void render(const Renderer* renderer) final override;
	void spark() override;
	void pulse(float deltaTime) override;
	

	RenderComponent* renderComponent() const;
	void setMaterial(Material* material);
	void setMesh(Mesh* mesh);
	TransformComponent* transformComponent();

private:
	TransformComponent* m_transformComp;
	RenderComponent* m_renderComp;
	DirectX::XMFLOAT4 color;
	Camera* m_camera;
	
};

}