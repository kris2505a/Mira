#include "MiraPch.h"
#include "ConstantBuffer.h"
#include "RHI.h"
#include "D3D11/D3D11ConstantBuffer.h"

namespace Mira {
Ref<ConstantBuffer> ConstantBuffer::create(const void *data, int size, ShaderType type) {

switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createRef<D3D11ConstantBuffer>(data, size, type);
    case API::None:
        break;
}

    return nullptr;
}
}
