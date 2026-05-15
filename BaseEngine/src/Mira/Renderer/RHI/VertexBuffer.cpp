#include "MiraPch.h"
#include "VertexBuffer.h"
#include "RHI.h"
#include "D3D11/D3D11VertexBuffer.h"

namespace Mira {

Scope<VertexBuffer> VertexBuffer::create(const void *data, int count, int stride, int offset) {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createScope<D3D11VertexBuffer>(data, count, stride, offset);
    case API::None:
        break;
    }
    return nullptr;
}

}
