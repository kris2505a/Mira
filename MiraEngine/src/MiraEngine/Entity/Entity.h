#pragma once
#include <MiraEngine/Core/MiraCore.h>

namespace Mira {

class MIRA_API Entity {
public:
	Entity();
	~Entity() = default;

	void update(float deltatime);
	void render(Renderer* renderer);

private:
	class Scene* p_scene;
	uint32_t m_entityId;
};

} //namespace ends