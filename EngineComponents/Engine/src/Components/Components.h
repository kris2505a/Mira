#pragma once
#include "Vec2D.h"

namespace Mira {

struct Component {

};

struct Transform {
	Vec2D position = Vec2D::zeroVec();
	float rotation = 0.0f;;
	Vec2D scale = Vec2D(1.0f);
	Vec2D size = Vec2D(1.0f);
};

}