#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Math/Vector.h>

namespace Mira {

struct MIRA_API TransformComponent {
	Vec2Df position;
	float rotation;
	Vec2Df scale;
};

} //namespace ends