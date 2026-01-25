#pragma once
#include "Component.hpp"
#include <DirectXMath.h>

namespace dx = DirectX;

class Camera : public Component {
public:
	Camera() {
		m_up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		setRotation(0.0f, 0.0f, 0.0f);
		m_position = dx::XMVectorZero();
		
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

		m_projection = dx::XMMatrixPerspectiveFovLH(
			dx::XM_PIDIV4,
			16.0f / 9.0f,
			0.1f,
			20.0f
		);
		m_active = true;
	}

	dx::XMMATRIX viewMat() {
		m_view = dx::XMMatrixLookAtLH(
			m_position,
			dx::XMVectorAdd(m_position, m_forward),
			m_up
		);
		return m_view;
	}

	const dx::XMMATRIX& projMat() const {
		return m_projection;
	}

	dx::XMVECTOR getPosition() const {
		return m_position;
	}

	dx::XMVECTOR getForwardVector() const {
		return m_forward;
	}

	dx::XMVECTOR getRightVector() const {
		return m_right;
	}

	float getPitch() const {
		return m_pitch;
	}

	float getYaw() const {
		return m_yaw;
	}

	void setPosition(dx::XMVECTOR vec) {
		m_position = vec;
	}

	void setRotation(float roll, float pitch, float yaw) {
		m_roll = roll;
		m_pitch = pitch;
		m_yaw = yaw;

		m_forward = dx::XMVector3Normalize(
			dx::XMVectorSet(
				cosf(m_pitch) * sinf(m_yaw),
				sinf(m_pitch),
				cosf(m_pitch) * cosf(m_yaw),
				0.0f
			)
		);

		m_right = dx::XMVector3Normalize(dx::XMVector3Cross(m_up, m_forward));
	}

	~Camera() override = default;

private:
	dx::XMVECTOR m_forward;
	dx::XMVECTOR m_right;
	dx::XMVECTOR m_up;
	dx::XMVECTOR m_position;

	dx::XMMATRIX m_view;
	dx::XMMATRIX m_projection;

	bool m_active;

	float m_roll;
	float m_pitch;
	float m_yaw;


};