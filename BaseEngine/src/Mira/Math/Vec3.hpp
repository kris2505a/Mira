#pragma once
#include "Vec2.hpp"
#include "Mira/Core/Core.hpp"

namespace Mira {

struct MIRA_API Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vec3() {}
    Vec3(float val) : x(val), y(val), z(val) {}
    Vec3(Vec2 vec, float _z) : x(vec.x), y(vec.y), z(_z) {}

    Vec3 operator+(const Vec3& other) const {
        return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    Vec3 operator*(float scale) const {
        return Vec3(this->x * scale, this->y * scale, this->z * scale);
    }

    Vec3 operator/(float scale) const {
        return Vec3(this->x / scale, this->y / scale, this->z / scale);
    }

    Vec3& operator+=(const Vec3& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vec3& operator*=(float scale) {
        this->x *= scale;
        this->y *= scale;
        this->z *= scale;
        return *this;
    }

    Vec3& operator/=(float scale) {
        this->x /= scale;
        this->y /= scale;
        this->z /= scale;
        return *this;
    }

    bool operator==(const Vec3& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    bool operator!=(const Vec3& other) const {
        return !(*this == other);
    }

};

}
