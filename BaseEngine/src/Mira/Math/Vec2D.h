#pragma once

namespace Mira {

struct Vec2D {
    float x = 0.0f;
    float y = 0.0f;

    Vec2D(float _x, float _y) : x(_x), y(_y) {}
    Vec2D() {}
    Vec2D(float val) : x(val), y(val) {}

    Vec2D operator+(const Vec2D& other) const {
        return Vec2D(this->x + other.x, this->y + other.y);
    }

    Vec2D operator-(const Vec2D& other) const {
        return Vec2D(this->x - other.x, this->y - other.y);
    }

    Vec2D operator*(float scale) const {
        return Vec2D(this->x * scale, this->y * scale);
    }

    Vec2D operator/(float scale) const {
        return Vec2D(this->x / scale, this->y / scale);
    }

    Vec2D& operator+=(const Vec2D& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vec2D& operator-=(const Vec2D& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vec2D& operator*=(float scale) {
        this->x *= scale;
        this->y *= scale;
        return *this;
    }

    Vec2D& operator/=(float scale) {
        this->x /= scale;
        this->y /= scale;
        return *this;
    }

    bool operator==(const Vec2D& other) const {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const Vec2D& other) const {
        return !(*this == other);
    }

};

}