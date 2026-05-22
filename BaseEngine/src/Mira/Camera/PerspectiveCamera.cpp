#include "MiraPch.hpp"
#include "PerspectiveCamera.hpp"
#include "Mira/Stats/EngineStats.hpp"

namespace Mira {

PerspectiveCamera::PerspectiveCamera() {
    reCalculateView();
    reCalculateProjection();
}

void PerspectiveCamera::setPosition(Vec3 pos) {
	m_position = pos;
    reCalculateView();
}
void PerspectiveCamera::setRotation(Rot3 rot) {
	m_rotation = rot;
    reCalculateView();
}
void PerspectiveCamera::setZoom(float zoom) {
	m_zoom = zoom;
    reCalculateView();
}

Vec3 PerspectiveCamera::getForwardVector() const {
    return m_forwardVector;
}

Vec3 PerspectiveCamera::getRightVector() const {
    return m_rightVector;
}

Vec3 PerspectiveCamera::getUpVector() const {
    return m_upVector;
}

Vec3 PerspectiveCamera::getPosition() const {
	return m_position;
}

Rot3 PerspectiveCamera::getRotation() const {
	return m_rotation;
}

float PerspectiveCamera::getZoom() const {
	return m_zoom;
}


void PerspectiveCamera::reCalculateView() {

    auto pos = DirectX::XMVectorSet(m_position.x, m_position.y, m_position.z, 1.0f);

    m_forwardVector.x = std::cosf(m_rotation.pitch) * std::sinf(m_rotation.yaw);
    m_forwardVector.y = std::sinf(m_rotation.pitch);
    m_forwardVector.z = std::cosf(m_rotation.pitch) * std::cosf(m_rotation.yaw);

    auto forward = DirectX::XMVectorSet(
        m_forwardVector.x,
        m_forwardVector.y,
        m_forwardVector.z,
        0.0f
    );

    forward = DirectX::XMVector3Normalize(forward);


    auto worldUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    auto right = DirectX::XMVector3Cross(worldUp, forward);

    right = DirectX::XMVector3Normalize(right);

    m_rightVector.x = DirectX::XMVectorGetX(right);
    m_rightVector.y = DirectX::XMVectorGetY(right);
    m_rightVector.z = DirectX::XMVectorGetZ(right);

    auto up = DirectX::XMVector3Cross(forward, right);


    auto rollRotation = DirectX::XMMatrixRotationAxis(forward, m_rotation.roll);

    up = DirectX::XMVector3TransformNormal(up, rollRotation);
    up = DirectX::XMVector3Normalize(up);
    
    

    auto target = DirectX::XMVectorAdd(pos, forward);

    auto viewMat = DirectX::XMMatrixLookAtLH(pos, target, up);


    setViewMat(viewMat);

}

void PerspectiveCamera::reCalculateProjection() {
    auto projection = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XM_PIDIV4,
        static_cast<float>(EngineStats::WindowProperties::getWidth()) / static_cast<float>(EngineStats::WindowProperties::getHeight()),
        0.1f,
        20.0f
    );

    setProjection(projection);
}

}