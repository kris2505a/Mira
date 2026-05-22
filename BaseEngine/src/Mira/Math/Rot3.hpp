#pragma once
#include "Mira/Core/Core.hpp"

namespace Mira {

struct MIRA_API Rot3 {
    float pitch = 0.0f;
    float yaw   = 0.0f;
    float roll  = 0.0f;

    Rot3(float _pitch, float _yaw, float _roll)
        : pitch(_pitch), yaw(_yaw), roll(_roll) {}

    Rot3() {}

    Rot3(float val)
        : pitch(val), yaw(val), roll(val) {}

    Rot3 operator+(const Rot3& other) const {
        return Rot3(
            pitch + other.pitch,
            yaw + other.yaw,
            roll + other.roll
        );
    }

    Rot3 operator-(const Rot3& other) const {
        return Rot3(
            pitch - other.pitch,
            yaw - other.yaw,
            roll - other.roll
        );
    }

    Rot3 operator*(float scale) const {
        return Rot3(
            pitch * scale,
            yaw * scale,
            roll * scale
        );
    }

    Rot3 operator/(float scale) const {
        return Rot3(
            pitch / scale,
            yaw / scale,
            roll / scale
        );
    }

    Rot3& operator+=(const Rot3& other) {
        pitch += other.pitch;
        yaw   += other.yaw;
        roll  += other.roll;
        return *this;
    }

    Rot3& operator-=(const Rot3& other) {
        pitch -= other.pitch;
        yaw   -= other.yaw;
        roll  -= other.roll;
        return *this;
    }

    Rot3& operator*=(float scale) {
        pitch *= scale;
        yaw   *= scale;
        roll  *= scale;
        return *this;
    }

    Rot3& operator/=(float scale) {
        pitch /= scale;
        yaw   /= scale;
        roll  /= scale;
        return *this;
    }

    bool operator==(const Rot3& other) const {
        return pitch == other.pitch &&
               yaw   == other.yaw &&
               roll  == other.roll;
    }

    bool operator!=(const Rot3& other) const {
        return !(*this == other);
    }
};

}