#include "MiraPch.hpp"
#include "Shader.hpp"
#include "RHI.hpp"
#include "D3D11/D3D11Shader.hpp"

namespace Mira {
Scope<Shader> Shader::create(const std::wstring& path, InputLayout layout) {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createScope<D3D11Shader>(path, layout);
    case API::None:
        break;
    }

    return nullptr;
}
}