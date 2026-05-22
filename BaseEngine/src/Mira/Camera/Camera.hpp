#pragma once

#include "Mira/Core/Core.hpp"
#include "Mira/Math/Vec3.hpp"

#include <DirectXMath.h>


namespace Mira {

class MIRA_API Camera {

public:
    Camera() = default;
    virtual ~Camera() = default;

    inline void setView(Vec3 eye, Vec3 target, Vec3 up) {
        auto view = DirectX::XMMatrixLookAtLH(
            DirectX::XMVectorSet(eye.x, eye.y, eye.z, 1.0f),
            DirectX::XMVectorSet(target.x, target.y, target.z, 1.0f),
            DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
        );

        //m_view = DirectX::XMMatrixInverse(nullptr, view);
        m_view = view;
    }

    inline void setViewMat(DirectX::XMMATRIX view) {
        m_view = view;
    }

    inline void setProjection(DirectX::XMMATRIX projection) {
        m_projection = projection;
    }

    [[nodiscard]]
    DirectX::XMMATRIX getViewProjection() const {
        return m_view * m_projection;
    }

    virtual void reCalculateView() = 0;
    virtual void reCalculateProjection() = 0;


private:
    DirectX::XMMATRIX m_view{};
    DirectX::XMMATRIX m_projection{};

};

}
