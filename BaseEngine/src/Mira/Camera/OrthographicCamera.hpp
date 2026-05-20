#pragma once
#include "Mira/Core/Core.hpp"
#include "Camera.hpp"

#include "Mira/Math/Vec2D.hpp"

namespace Mira {

class MIRA_API OrthographicCamera : public Camera {
public:
    OrthographicCamera();
    
    void setViewWidthHeight(float width, float height);

    void setPosition(Vec2D pos);
    void setRotation(float theta);
    void setZoom(float zoom);

    Vec2D getPosition() const;
    float getRotation() const;
    float getZoom() const;

private:
    void reCalculateView();
    void reCalculateProjection();

private:
    Vec2D m_position;
    float m_rotation;
    float m_zoom;
    float m_viewWidth;
    float m_viewHeight;
};

}
