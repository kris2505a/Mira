#pragma once
#include "RHI/VertexBuffer.h"
#include "RHI/IndexBuffer.h"
#include "Mira/Core/MemoryType.h"

namespace Mira {

class Mesh {
    friend class InstanceManager;
public:
    Mesh() = default;
    ~Mesh() = default;

    void bind() const;
    uint32_t getIndexCount() const;

private:
    Scope<VertexBuffer> m_vertexBuffer;
    Scope<IndexBuffer> m_indexBuffer;
};

}
