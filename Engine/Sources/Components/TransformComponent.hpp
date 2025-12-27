#pragma once
#include "Core/Core.hpp"
#include <DirectXMath.h>
#include "Component.hpp"

#define RAD(x) DirectX::XMConvertToRadians(x)

namespace Mira {

struct TransformComponent : public Component {
	DirectX::XMMATRIX model() {
		return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
			DirectX::XMMatrixRotationRollPitchYaw(RAD(rotation.x), RAD(rotation.y), RAD(rotation.z)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}

	DirectX::XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 rotation = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 scale = { 1.0f, 1.0f, 1.0f };
};

}