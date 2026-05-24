#include "MiraPch.hpp"
#include "Shader.hpp"
#include "RHI.hpp"
#include "D3D11/D3D11Shader.hpp"

namespace Mira {
Ref<Shader> Shader::create(const std::wstring& path, const InputLayout& layout) {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createRef<D3D11Shader>(path, layout);
    case API::None:
        break;
    }

    return nullptr;
}
}