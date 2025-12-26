#pragma once
#include "Core/Core.hpp"
#include <DirectXMath.h>


namespace Mira {

namespace dx = DirectX;

class MIRA_API Camera {
public:
	Camera();
	~Camera() = default;
	void pulse(float deltaTime);
	dx::XMMATRIX& view();
	dx::XMMATRIX& projection();

private:
	dx::XMVECTOR m_forward;
	dx::XMVECTOR m_right;
	dx::XMVECTOR m_up;
	dx::XMVECTOR m_position;

	dx::XMMATRIX m_view;
	dx::XMMATRIX m_projection;

	float m_pitch;
	float m_yaw;
	float m_zoom;
	float m_sensitivity;
	float m_speed;
};

}