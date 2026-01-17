#pragma once
#include "Components/Transform.hpp"
#include "Rendering/Mesh.hpp"
#include "Rendering/Material.hpp"

class Entity {
	friend class Renderer;
public:
	Entity(std::unique_ptr <Mesh> mesh, std::unique_ptr <Material> material);
	virtual void update(float deltaTime) = 0;
	virtual ~Entity() = default;
	
	//getters
	DirectX::XMFLOAT3 getPosition() const;
	DirectX::XMFLOAT3 getRotation() const;
	DirectX::XMFLOAT3 getScale() const;
	Material* getMaterial();
	Mesh* getMesh();

	//setters
	void setPosition(DirectX::XMFLOAT3 position);
	void setRotation(DirectX::XMFLOAT3 rotation);
	void setScale(DirectX::XMFLOAT3 scale);
	
private:
	const Transform& getTransform() const;



private:
	Transform m_transform;
	std::unique_ptr <Mesh> m_mesh;
	std::unique_ptr <Material> m_material;
	
};