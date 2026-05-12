#pragma once
#include "Mira/Core/MemoryType.h"
#include "ShaderType.h"

namespace Mira {

class ConstantBuffer {
public:
    ConstantBuffer() = default;
    virtual ~ConstantBuffer() = default;
    virtual void bind() const = 0;
    virtual void update(const void* data, int size) = 0;

    static Ref<ConstantBuffer> create(const void* data, int size, ShaderType type);
};

}