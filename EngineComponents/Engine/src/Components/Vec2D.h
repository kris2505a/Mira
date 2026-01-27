#pragma once

namespace Mira {

struct Vec2D {
	float x;
	float y;


	constexpr Vec2D(float _x, float _y) noexcept : x(_x), y(_y) {

	}

	constexpr Vec2D() noexcept : x(0.0f), y(0.0f) {

	}

	static constexpr Vec2D zeroVec() noexcept {
		return Vec2D(0.0f, 0.0f);
	}

	static constexpr float dot(const Vec2D& v1, const Vec2D& v2) noexcept {
		return v1.x * v2.x + v1.y * v2.y;
	}

	constexpr Vec2D operator+(const Vec2D& other) const noexcept {
		return { this->x + other.x, this->y + other.y };
	}

	constexpr Vec2D operator-(const Vec2D& other) const noexcept {
		return { this->x - other.x, this->y - other.y };
	}

	constexpr Vec2D& operator+=(const Vec2D& other) noexcept {
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	constexpr Vec2D& operator-=(const Vec2D& other) noexcept {
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	constexpr Vec2D operator*(const Vec2D& other) const noexcept {
		return { this->x * other.x, this->y * other.y };
	}

};

}