#include "MiraPch.hpp"
#include "OrthographicCamera.hpp"
#include "Mira/Math/Vec3D.hpp"


namespace Mira {

namespace dx = DirectX;

OrthographicCamera::OrthographicCamera() 
        : m_position(0.0f), m_rotation(0), m_zoom(1.0f), m_viewWidth(1280.0f), m_viewHeight(720.0f) {
    
    reCalculateView();
    reCalculateProjection();
}

void OrthographicCamera::setViewWidthHeight(float width, float height) {
    m_viewWidth = width;
    m_viewHeight = height;

    reCalculateView();
    reCalculateProjection();
}

Vec2D OrthographicCamera::getPosition() const {
    return m_position;
}

float OrthographicCamera::getRotation() const {
    return m_rotation;
}

float OrthographicCamera::getZoom() const {
    return m_zoom;
}

void OrthographicCamera::setPosition(Vec2D pos) {
    m_position = pos;
    reCalculateView();
}

void OrthographicCamera::setRotation(float theta) {
    m_rotation = theta;
    reCalculateView();
}

void OrthographicCamera::setZoom(float zoom) {
    m_zoom = zoom;
    reCalculateProjection();
}

void OrthographicCamera::reCalculateView() {
    auto theta = dx::XMConvertToRadians(m_rotation);

    Vec3D up(
        -std::sinf(theta),
        std::cosf(theta),
        0.0f
    );

    setView(
        Vec3D(m_position, 1.0f),
        Vec3D(m_position, 1.0f) + Vec3D(0.0f, 0.0f, 1.0f),
        up
    );
}

void OrthographicCamera::reCalculateProjection() {
    auto projection = dx::XMMatrixOrthographicLH(
        m_viewWidth / m_zoom, 
        m_viewHeight / m_zoom,
        -1.0f,
        1.0f
    );

    setProjection(projection);
}
    
}
