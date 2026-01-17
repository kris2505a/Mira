#include "Entity.hpp"
#include "Rendering/Renderer.hpp"


Entity::Entity(std::unique_ptr<Mesh> mesh, std::unique_ptr<Material> material)
	: m_mesh(std::move(mesh)), m_material(std::move(material)) {

}

DirectX::XMFLOAT3 Entity::getPosition() const {
	return m_transform.position;
}

DirectX::XMFLOAT3 Entity::getRotation() const {
	return m_transform.rotation;
}

DirectX::XMFLOAT3 Entity::getScale() const {
	return m_transform.scale;
}

void Entity::setPosition(DirectX::XMFLOAT3 position) {
	m_transform.position = position;
}

void Entity::setRotation(DirectX::XMFLOAT3 rotation) {
	m_transform.rotation = rotation;
}

void Entity::setScale(DirectX::XMFLOAT3 scale) {
	m_transform.scale = scale;
}

const Transform& Entity::getTransform() const {
	return m_transform;
}

Material* Entity::getMaterial() {
	return m_material.get();
}

Mesh* Entity::getMesh() {
	return m_mesh.get();
}
