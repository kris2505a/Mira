#pragma once

#include "Mira/Renderer/Mesh.hpp"
#include "Mira/Renderer/Material.hpp"
#include "Mira/Core/Core.hpp"

#include <glm/vec4.hpp>

#include "Mira/Math/Vec3.hpp"
#include "Mira/Math/Rot3.hpp"


namespace Mira {

struct Component {};


struct MIRA_API RenderComponent : public Component {
    Ref<Mesh> mesh;
    Ref<Material> material;

    glm::vec4 color;

};

struct MIRA_API TransformComponent : public Component {
    Vec3 position = { 0.0f, 0.0f, 0.0f };
    Rot3 rotation = { 0.0f, 0.0f, 0.0f };
    Vec3 scale = { 1.0f, 1.0f, 1.0f };
};



}