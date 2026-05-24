#include "MiraPch.hpp"
#include "PerspectiveCamera.hpp"
#include "Mira/Stats/EngineStats.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    m_forwardVector.x = std::cosf(m_rotation.pitch) * std::sinf(m_rotation.yaw);
    m_forwardVector.y = std::sinf(m_rotation.pitch);
    m_forwardVector.z = std::cosf(m_rotation.pitch) * std::cosf(m_rotation.yaw);



    glm::vec3 forward(m_forwardVector.x, m_forwardVector.y, m_forwardVector.z);
    
    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

    forward = glm::normalize(forward);

    auto right = glm::cross(worldUp, forward);

    auto up = glm::cross(forward, right);

    auto rollRotation = glm::rotate(glm::mat4(1.0f), m_rotation.roll, forward);

    up = glm::normalize(
        glm::vec3(rollRotation * glm::vec4(up, 1.0f))
    );

    glm::vec3 position(m_position.x, m_position.y, m_position.z);

    auto view = glm::lookAtLH(
        position,
        position + forward,
        up
    );

    m_rightVector.x = right.x;
    m_rightVector.y = right.y;
    m_rightVector.z = right.z;

    m_upVector.x = up.x;
    m_upVector.y = up.y;
    m_upVector.z = up.z;

    setViewMat(view);

}

void PerspectiveCamera::reCalculateProjection() {

    auto projection = glm::perspectiveFovLH(
        glm::radians(45.0f),
        static_cast<float>(EngineStats::WindowProperties::getWidth()),
        static_cast<float>(EngineStats::WindowProperties::getHeight()),
        0.1f, 20.0f
    );

    setProjection(projection);
}

}