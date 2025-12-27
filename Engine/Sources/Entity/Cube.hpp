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
	Cube(Camera* camera);
	~Cube();

	void render(Renderer* renderer) final override;
	void renderUI();
	void spark() override;
	void pulse(float deltaTime) override;
	

	RenderComponent* renderComponent() const;
	void setMaterial(Material* material);
	void setMesh(Mesh* mesh);
	TransformComponent* transformComponent();

private:
	TransformComponent* m_transformComp;
	RenderComponent* m_renderComp;
	Camera* p_camera;
	ConstantBuffer* m_vcbo;
};

}