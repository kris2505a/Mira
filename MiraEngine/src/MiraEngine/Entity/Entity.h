#pragma once
#include <MiraEngine/Core/MiraCore.h>

namespace Mira {

class MIRA_API Entity {
public:
	Entity(class Scene* _sceneRef, uint32_t _entityId);
	~Entity() = default;

private:
	class Scene* p_scene;
	uint32_t m_entityId;
};

} //namespace ends