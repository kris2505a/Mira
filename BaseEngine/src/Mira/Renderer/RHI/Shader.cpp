#include "MiraPch.h"
#include "Shader.h"
#include "RHI.h"
#include "D3D11/D3D11Shader.h"

namespace Mira {
Scope<Shader> Shader::create(const std::wstring &path, InputLayout layout) {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createScope<D3D11Shader>(path, layout);
    case API::None:
        break;
    }

    return nullptr;
}
}
