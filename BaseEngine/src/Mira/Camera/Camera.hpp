#pragma once

#include "Mira/Core/Core.hpp"
#include "Mira/Math/Vec3D.hpp"

#include <DirectXMath.h>


namespace Mira {

class MIRA_API Camera {

public:
    Camera() = default;
    ~Camera() = default;

    inline void setView(Vec3D eye, Vec3D target, Vec3D up) {
        auto view = DirectX::XMMatrixLookAtLH(
            DirectX::XMVectorSet(eye.x, eye.y, eye.z, 1.0f),
            DirectX::XMVectorSet(target.x, target.y, target.z, 1.0f),
            DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
        );

        //m_view = DirectX::XMMatrixInverse(nullptr, view);
        m_view = view;
    }

    inline void setProjection(DirectX::XMMATRIX projection) {
        m_projection = projection;
    }

    DirectX::XMMATRIX getViewProjection() const {
        return m_view * m_projection;
    }

private:
    DirectX::XMMATRIX m_view;
    DirectX::XMMATRIX m_projection;

};

}
