#pragma once
#include "Mira/Core/MemoryType.h"

namespace Mira {

class VertexBuffer {
public:
    VertexBuffer() = default;
    virtual ~VertexBuffer() = default;
    virtual void bind() const = 0;
    static Ref<VertexBuffer> create(const void* data, int count, int stride, int offset = 0);
};

}