#include <PreCompHeader.hpp>
#include "Camera.hpp"
#include "Win32/Mouse.hpp"
#include "Input/Input.hpp"

namespace Mira {

Camera::Camera()
	: m_zoom(-15.0f), m_pitch(0.0f), m_yaw(0.0f), m_sensitivity(0.005f), m_speed(1.0f) {
	
	m_position = dx::XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f);
	m_up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	
	m_forward = dx::XMVector3Normalize(
		dx::XMVectorSet(
			cosf(m_pitch) * sinf(m_yaw),
			sinf(m_pitch),
			cosf(m_pitch) * cosf(m_yaw),
			0.0f
		)
	);

	m_right = dx::XMVector3Normalize(dx::XMVector3Cross(m_up, m_forward));
	m_view = dx::XMMatrixLookAtLH(
		m_position,
		dx::XMVectorAdd(m_position, m_forward),
		m_up
	);

	m_projection = dx::XMMatrixPerspectiveFovLH(dx::XM_PIDIV4, 16.0f / 9.0f, 0.01f, 100.0f);
}

void Camera::pulse(float deltaTime) {


	if (Input::buttonDown(Button::MouseRight)) {
		m_yaw += Mouse::xDelta() * m_sensitivity;
		m_pitch -= Mouse::yDelta() * m_sensitivity;
	}

	m_pitch = std::clamp(m_pitch, -dx::XM_PIDIV2 + 0.01f, dx::XM_PIDIV2 - 0.01f);

	m_forward = dx::XMVector3Normalize(
		dx::XMVectorSet(
			cosf(m_pitch) * sinf(m_yaw),
			sinf(m_pitch),
			cosf(m_pitch) * cosf(m_yaw),
			0.0f
		)
	);

	m_right = dx::XMVector3Normalize(dx::XMVector3Cross(m_up, m_forward));

	if (Input::keyDown(Key::W)) 
		m_position = dx::XMVectorAdd(m_position, dx::XMVectorScale(m_forward, m_speed * deltaTime));
	if (Input::keyDown(Key::S))
		m_position = dx::XMVectorSubtract(m_position, dx::XMVectorScale(m_forward, m_speed * deltaTime));
	if (Input::keyDown(Key::D)) 
		m_position = dx::XMVectorAdd(m_position, dx::XMVectorScale(m_right, m_speed * deltaTime));
	if (Input::keyDown(Key::A)) 
		m_position = dx::XMVectorSubtract(m_position, dx::XMVectorScale(m_right, m_speed * deltaTime));

	m_view = dx::XMMatrixLookAtLH(m_position, dx::XMVectorAdd(m_position, m_forward), m_up);

}

dx::XMMATRIX& Camera::view() {
	return m_view;
}

dx::XMMATRIX& Camera::projection() {
	return m_projection;
}

}