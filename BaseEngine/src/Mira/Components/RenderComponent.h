#pragma once
#include "Mira/Renderer/Mesh.h"
#include "Mira/Renderer/Material.h"
#include <DirectXMath.h>

namespace Mira {

struct RenderComponent {
    Ref<Mesh> mesh;
    Ref<Material> material;

    DirectX::XMMATRIX modelMatrix;
    DirectX::XMFLOAT4 color;    

};
    
}
