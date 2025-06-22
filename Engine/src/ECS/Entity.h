#pragma once
#include "Scene.h"
#include <Core.h>
#include <cstdint>

class API Entity {
private:
	uint32_t m_entityId;
	Scene* p_scene;

public:
	Entity(Scene* scene, const uint32_t id);
};