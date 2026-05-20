#pragma once
#include "Mira/Core/MemoryType.hpp"

namespace Mira {

class VertexBuffer {
public:
    VertexBuffer() = default;
    virtual ~VertexBuffer() = default;
    virtual void bind() const = 0;
    static Scope<VertexBuffer> create(const void* data, int count, int stride, int offset = 0);
};

}