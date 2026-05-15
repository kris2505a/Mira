#include "MiraPch.h"
#include "Mesh.h"

namespace Mira {

void Mesh::bindMesh() const {
    m_vertexBuffer->bind();
    m_indexBuffer->bind();
}

uint32_t Mesh::getIndexCount() const {
    return m_indexBuffer->getCount();
}

}