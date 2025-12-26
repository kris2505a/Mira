#pragma once
#include "Core/Core.hpp"
#include <DirectXMath.h>

namespace Mira {

class Transform {
public:
	Transform();
	~Transform() = default;
	DirectX::XMFLOAT3& position();
	DirectX::XMFLOAT3& rotation();
	DirectX::XMFLOAT3& scale();
	DirectX::XMMATRIX& model();

private:
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_scale;
	DirectX::XMMATRIX m_model;
};

}