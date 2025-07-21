#pragma once
#include <MiraEngine/Core/MiraCore.h>

namespace Mira {

struct MIRA_API Vec2Df {
	float x, y;
	Vec2Df(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {
	}

	Vec2Df operator+(const Vec2Df& other) const {
		return Vec2Df(this->x + other.x, this->y + other.y);
	}

	Vec2Df operator-(const Vec2Df& other) const {
		return Vec2Df(this->x - other.x, this->y - other.y);
	}
};

} //namespace ends