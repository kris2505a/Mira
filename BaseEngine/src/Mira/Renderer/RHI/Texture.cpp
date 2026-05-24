#include "MiraPch.hpp"
#include "Texture.hpp"
#include "RHI.hpp"
#include "D3D11/D3D11Texture.hpp"

namespace Mira {
Ref<Texture> Texture::create(const std::string& path) {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createRef<D3D11Texture>(path);
    case API::None:
        break;
    }

    return nullptr;
}

Ref<Texture> Texture::create() {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createRef<D3D11Texture>(0xffffffff);
    case API::None:
        break;
    }

    return nullptr;
}

}