#pragma once

#include "Mira/Core/Core.hpp"
#include "Mira/Math/Vec3.hpp"
#include "Mira/Math/Rot3.hpp"

#include "Camera.hpp"

namespace Mira {

class MIRA_API PerspectiveCamera : public Camera {
public:
    PerspectiveCamera();

    void setPosition(Vec3 pos);
    void setRotation(Rot3 rot);
    void setZoom(float zoom);

    Vec3 getForwardVector() const;
    Vec3 getRightVector() const;
    Vec3 getUpVector() const;



    Vec3 getPosition() const;
    Rot3 getRotation() const;
    float getZoom() const;

    void reCalculateView();
    void reCalculateProjection();

private:
    Vec3 m_position;
    Rot3 m_rotation;

    Vec3 m_forwardVector;
    Vec3 m_rightVector;
    Vec3 m_upVector;

    float m_zoom{ 1.0f };
};

}