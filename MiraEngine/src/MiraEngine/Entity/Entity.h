#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Scene/Scene.h>

namespace Mira {

class MIRA_API Entity {
public:
	Entity() = default;
	~Entity() = default;

private:
	Scene* p_scene;
};

} //namespace ends