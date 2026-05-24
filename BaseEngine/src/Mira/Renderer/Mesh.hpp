#pragma once
#include "RHI/VertexBuffer.hpp"
#include "RHI/IndexBuffer.hpp"
#include "Mira/Core/MemoryType.hpp"

namespace Mira {

class Mesh {
    friend class RenderResourceManager;
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
