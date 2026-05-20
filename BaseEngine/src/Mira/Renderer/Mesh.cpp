#include "MiraPch.hpp"
#include "Mesh.hpp"

namespace Mira {

void Mesh::bind() const {
    m_vertexBuffer->bind();
    m_indexBuffer->bind();
}

uint32_t Mesh::getIndexCount() const {
    return m_indexBuffer->getCount();
}

}