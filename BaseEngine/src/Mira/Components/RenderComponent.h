#pragma once
#include "Mira/Renderer/Mesh.h"
#include "Mira/Renderer/Material.h"
#include <DirectXMath.h>
#include "Mira/Core/Core.h"

namespace Mira {

struct MIRA_API RenderComponent {
    Ref<Mesh> mesh;
    Ref<Material> material;

    DirectX::XMMATRIX modelMatrix;
    DirectX::XMFLOAT4 color;    

};
    
}
