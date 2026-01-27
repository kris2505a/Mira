#pragma once
#include <DirectXMath.h>

namespace dxr {

struct Vertex3 {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;
};

}