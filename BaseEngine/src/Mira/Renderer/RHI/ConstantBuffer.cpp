#include "MiraPch.hpp"
#include "ConstantBuffer.hpp"
#include "RHI.hpp"
#include "D3D11/D3D11ConstantBuffer.hpp"

namespace Mira {
Scope<ConstantBuffer> ConstantBuffer::create(const void *data, int size, ShaderType type) {

switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createScope<D3D11ConstantBuffer>(data, size, type);
    case API::None:
        break;
}

    return nullptr;
}
}
