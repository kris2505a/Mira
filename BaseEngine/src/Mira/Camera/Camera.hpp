#pragma once

#include "Mira/Core/Core.hpp"
#include "Mira/Math/Vec3.hpp"

#include <glm/mat4x4.hpp>

namespace Mira {

class MIRA_API Camera {

public:
    Camera() = default;
    virtual ~Camera() = default;

    inline void setViewMat(glm::mat4 view) {
        m_view = view;
    }

    inline void setProjection(glm::mat4 projection) {
        m_projection = projection;
    }

    [[nodiscard]]
    glm::mat4 getViewProjection() const {
        return m_projection * m_view;
    }

    virtual void reCalculateView() = 0;
    virtual void reCalculateProjection() = 0;


private:
    glm::mat4 m_view{};
    glm::mat4 m_projection{};

};

}
