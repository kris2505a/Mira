#pragma once
#include <Drawable.h>
#include "Components/Components.h"
 
namespace Mira {

class Entity : public dxr::Drawable {
public:
	Entity();
	~Entity() = default;
	DirectX::XMMATRIX getModelMatrix() const final override;
	void bind() const final override;
	unsigned int getIndexCount() const final override;
	DirectX::XMFLOAT4 getColor() const final override;
	virtual bool hasTexture() const = 0;

//getters and setters
public:
	//Vectors
	Vec2D getRightVector() const;
	Vec2D getUpVector() const;

	//Local
	Vec2D getLocalPosition() const;
	float getLocalRotation() const;
	Vec2D getLocalScale() const;

	void setLocalPosition(Vec2D vector);
	void setLocalRotation(float degree);
	void setLocalScale(Vec2D scale);

	//Global
	Vec2D getGlobalPosition() const;
	float getGlobalRotation() const;
	Vec2D getGlobalScale() const;

	void setGlobalPosition(Vec2D vector);
	void setGlobalRotation(float degree);
	void setGlobalScale(Vec2D scale);
	
	void setParent(Entity* parent);

//Lifetime Methods
public:
	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;

private:
	Transform m_transform;
	Vec2D m_size;
	Entity* p_parent;
};

}