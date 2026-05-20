#include "MiraPch.hpp"
#include "IndexBuffer.hpp"
#include "RHI.hpp"
#include "D3D11/D3D11IndexBuffer.hpp"

namespace Mira {
Scope<IndexBuffer> IndexBuffer::create(const void *indices, int count, int offset) {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createScope<D3D11IndexBuffer>(indices, count, offset);
    case API::None:
        break;
    }

    return nullptr;
}
}
