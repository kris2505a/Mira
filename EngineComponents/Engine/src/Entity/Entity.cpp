#include "Entity.h"

namespace Mira {

auto degToRad = [](float deg) {
	return DirectX::XMConvertToRadians(deg);
	};

DirectX::XMMATRIX Entity::getModelMatrix() const {
	auto local = DirectX::XMMATRIX(
		DirectX::XMMatrixScaling(m_transform.scale.x * m_transform.size.x, m_transform.scale.y * m_transform.size.y, 1.0f) *
		DirectX::XMMatrixRotationZ(degToRad(m_transform.rotation)) *
		DirectX::XMMatrixTranslation(m_transform.position.x, m_transform.position.y, 0.0f)
	);
	if (!p_parent) {
		return local;
	}

	return local * p_parent->getModelMatrix();
}

void Entity::bind() const {

}

unsigned int Entity::getIndexCount() const {
	return 0;
}

DirectX::XMFLOAT4 Entity::getColor() const {
	return DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
}

Vec2D Entity::getRightVector() const {
	return { cosf(degToRad(m_transform.rotation)), sinf(degToRad(m_transform.rotation)) };
}

Vec2D Entity::getUpVector() const {
	return { -sinf(degToRad(m_transform.rotation)), cosf(degToRad(m_transform.rotation)) };
}

Vec2D Entity::getLocalPosition() const {
	return m_transform.position;
}

float Entity::getLocalRotation() const {
	return m_transform.rotation;
}

Vec2D Entity::getLocalScale() const {
	return m_transform.scale;
}

void Entity::setLocalPosition(Vec2D vector) {
	m_transform.position = vector;
}

void Entity::setLocalRotation(float degree) {
	m_transform.rotation = degree;
}

void Entity::setLocalScale(Vec2D scale) {
	m_transform.scale = scale;
}

Vec2D Entity::getGlobalPosition() const {
	if (!p_parent) {
		return this->getLocalPosition();
	}

	Vec2D parentPos = p_parent->getGlobalPosition();
	float parentRot = degToRad(p_parent->getGlobalRotation());
	Vec2D parentScale = p_parent->getGlobalScale();

	Vec2D local = this->getLocalPosition();
	
	local.x *= parentScale.x;
	local.y *= parentScale.y;

	float c = cosf(parentRot);
	float sn = sinf(parentRot);

	Vec2D rotated{
		local.x * c - local.y * sn,
		local.x * sn + local.y * c
	};

	return parentPos + rotated;

}

float Entity::getGlobalRotation() const {
	if (!p_parent)
		return m_transform.rotation;
	return m_transform.rotation + p_parent->getGlobalRotation();
}

Vec2D Entity::getGlobalScale() const {
	if (!p_parent)
		return m_transform.scale;
	return m_transform.scale * p_parent->getGlobalScale();
}

void Entity::setGlobalPosition(Vec2D vector) {
	if (p_parent) {
		p_parent->setGlobalPosition(vector);
		return;
	}
	this->setLocalPosition(vector);
}

void Entity::setGlobalRotation(float degree) {
	if (p_parent) {
		p_parent->setGlobalRotation(degree);
		return;
	}
	this->setLocalRotation(degree);
}

void Entity::setGlobalScale(Vec2D scale) {
	if (p_parent) {
		p_parent->setGlobalScale(scale);
		return;
	}
	this->setLocalScale(scale);
}

void Entity::setParent(Entity* parent) {
	p_parent = parent;
}

}