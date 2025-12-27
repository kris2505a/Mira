#pragma once
#include "Core/Core.hpp"
#include "Drawable.hpp"
#include <cstdint>
#include "Components/Component.hpp"
#include "Components/RenderComponent.hpp"
#include "Components/TransformComponent.hpp"
#include <type_traits>

namespace Mira {

class MIRA_API Entity : public Drawable {
public:
	Entity();
	~Entity();
	
	virtual void render(Renderer* renderer) {};
	virtual void spark() {}
	virtual void pulse(float deltaTime) {}
	uint32_t id() const;

private:
	uint32_t m_id;
	class Scene* p_parentScene;
};

}