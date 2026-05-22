#pragma once

#include "Mira/Core/Core.hpp"


namespace Mira {

struct MIRA_API Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    Vec2(float _x, float _y) : x(_x), y(_y) {}
    Vec2() {}
    Vec2(float val) : x(val), y(val) {}

    Vec2 operator+(const Vec2& other) const {
        return Vec2(this->x + other.x, this->y + other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2(this->x - other.x, this->y - other.y);
    }

    Vec2 operator*(float scale) const {
        return Vec2(this->x * scale, this->y * scale);
    }

    Vec2 operator/(float scale) const {
        return Vec2(this->x / scale, this->y / scale);
    }

    Vec2& operator+=(const Vec2& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vec2& operator*=(float scale) {
        this->x *= scale;
        this->y *= scale;
        return *this;
    }

    Vec2& operator/=(float scale) {
        this->x /= scale;
        this->y /= scale;
        return *this;
    }

    bool operator==(const Vec2& other) const {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const Vec2& other) const {
        return !(*this == other);
    }

};

}