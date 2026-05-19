#pragma once
#include "Mira/Core/Core.h"
#include "Mira/Math/Vec3D.h"

namespace Mira {

struct MIRA_API TransformComponent {
    Vec3D position = { 0.0f, 0.0f, 0.0f };
    Vec3D rotation = { 0.0f, 0.0f, 0.0f };
    Vec3D scale = { 1.0f, 1.0f, 1.0f };
};
    
}
