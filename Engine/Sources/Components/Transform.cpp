#include <PreCompHeader.hpp>
#include "Transform.hpp"

namespace Mira {

Transform::Transform() {
	m_position = { 0.0f, 0.0f, 0.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };
	m_scale	   = { 1.0f, 1.0f, 1.0f };
}

DirectX::XMFLOAT3& Transform::position() {
	return m_position;
}

DirectX::XMFLOAT3& Transform::rotation() {
	return m_rotation;
}

DirectX::XMFLOAT3& Transform::scale() {
	return m_scale;
}

DirectX::XMMATRIX& Transform::model() {
	m_model = DirectX::XMMATRIX(
		DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
		DirectX::XMMatrixRotationRollPitchYaw(
			DirectX::XMConvertToRadians(m_rotation.x),
			DirectX::XMConvertToRadians(m_rotation.y),
			DirectX::XMConvertToRadians(m_rotation.z)
		) *
		DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z)
);

	return m_model;
}


}