#include "MiraPch.h"
#include "IndexBuffer.h"
#include "RHI.h"
#include "D3D11/D3D11IndexBuffer.h"

namespace Mira {
Ref<IndexBuffer> IndexBuffer::create(const void *indices, int count, int offset) {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createRef<D3D11IndexBuffer>(indices, count, offset);
    case API::None:
        break;
    }

    return nullptr;
}
}
