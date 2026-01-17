#pragma once
#include "Component.hpp"
#include <DirectXMath.h>

namespace dx = DirectX;

class Camera : public Component {
public:
	Camera() {
		this->position = dx::XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f);
		this->up = dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		this->pitch = 0.0f;
		this->yaw = 0.0f;
		
		this->forward = dx::XMVector3Normalize(
			dx::XMVectorSet(
				cosf(this->pitch) * sinf(this->yaw),
				sinf(this->pitch),
				cosf(this->pitch) * cosf(this->yaw),
				0.0f
			)
		);

		this->right = dx::XMVector3Normalize(dx::XMVector3Cross(this->up, this->forward));
		
		this->view = dx::XMMatrixLookAtLH(
			this->position,
			dx::XMVectorAdd(this->position, this->forward),
			this->up
		);

		this->projection = dx::XMMatrixPerspectiveFovLH(
			dx::XM_PIDIV4,
			16.0f / 9.0f,
			0.1f,
			20.0f
		);
		this->active = true;
	}

	dx::XMMATRIX viewMat() {
		this->view = dx::XMMatrixLookAtLH(
			this->position,
			dx::XMVectorAdd(this->position, this->forward),
			this->up
		);
		return this->view;
	}

	~Camera() override = default;


	dx::XMVECTOR forward;
	dx::XMVECTOR right;
	dx::XMVECTOR up;
	dx::XMVECTOR position;

	dx::XMMATRIX view;
	dx::XMMATRIX projection;

	bool active;

	float pitch;
	float yaw;


};