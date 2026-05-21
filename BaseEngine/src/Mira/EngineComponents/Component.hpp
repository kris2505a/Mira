#pragma once

#include "Mira/Renderer/Mesh.hpp"
#include "Mira/Renderer/Material.hpp"
#include <DirectXMath.h>
#include "Mira/Core/Core.hpp"

#include "Mira/Math/Vec3D.hpp"


namespace Mira {

struct Component {};


struct MIRA_API RenderComponent : public Component {
    Ref<Mesh> mesh;
    Ref<Material> material;

    DirectX::XMMATRIX modelMatrix{ DirectX::XMMatrixIdentity() };
    DirectX::XMFLOAT4 color{ 0.0f, 0.0f, 0.0f, 0.0f };

};

struct MIRA_API TransformComponent : public Component {
    Vec3D position = { 0.0f, 0.0f, 0.0f };
    Vec3D rotation = { 0.0f, 0.0f, 0.0f };
    Vec3D scale = { 1.0f, 1.0f, 1.0f };
};



}