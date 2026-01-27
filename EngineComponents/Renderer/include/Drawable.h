#pragma once
#include <DirectXMath.h>

namespace dxr {

class Drawable {
public:
    virtual DirectX::XMMATRIX getModelMatrix() const = 0;
    virtual void bind() const = 0;
    virtual unsigned int getIndexCount() const = 0;
    virtual bool hasTexture() const = 0;
    virtual DirectX::XMFLOAT4 getColor() const = 0;
};

}