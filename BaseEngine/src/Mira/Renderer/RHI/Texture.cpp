#include "MiraPch.h"
#include "Texture.h"
#include "RHI.h"
#include "D3D11/D3D11Texture.h"

namespace Mira {
Ref<Texture> Texture::create(const std::string &path) {

    switch (RHI::getCurrentAPI()) {
    case API::D3D11:
        return createRef<D3D11Texture>(path);
    case API::None:
        break;
    }

    return nullptr;
}
}
