#pragma once
#include "Mira/Core/MemoryType.h"

namespace Mira {

class IndexBuffer {
public:
    IndexBuffer() = default;
    virtual ~IndexBuffer() = default;
    virtual void bind() const = 0;
    virtual unsigned int getCount() const = 0;

    static Ref<IndexBuffer> create(const void* indices, int count, int offset = 0);
};

}