#pragma once
#include "Vec2D.h"

namespace Mira {

struct Vec3D {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vec3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vec3D() {}
    Vec3D(float val) : x(val), y(val), z(val) {}
    Vec3D(Vec2D vec, float _z) : x(vec.x), y(vec.y), z(_z) {}

    Vec3D operator+(const Vec3D& other) const {
        return Vec3D(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Vec3D operator-(const Vec3D& other) const {
        return Vec3D(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    Vec3D operator*(float scale) const {
        return Vec3D(this->x * scale, this->y * scale, this->z * scale);
    }

    Vec3D operator/(float scale) const {
        return Vec3D(this->x / scale, this->y / scale, this->z / scale);
    }

    Vec3D& operator+=(const Vec3D& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vec3D& operator-=(const Vec3D& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vec3D& operator*=(float scale) {
        this->x *= scale;
        this->y *= scale;
        this->z *= scale;
        return *this;
    }

    Vec3D& operator/=(float scale) {
        this->x /= scale;
        this->y /= scale;
        this->z /= scale;
        return *this;
    }

    bool operator==(const Vec3D& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    bool operator!=(const Vec3D& other) const {
        return !(*this == other);
    }

};

}
