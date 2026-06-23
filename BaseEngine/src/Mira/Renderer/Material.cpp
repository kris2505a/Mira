#include "MiraPch.hpp"
#include "Material.hpp"

namespace Mira {

void Material::bind(int textureSlot) const {
    shader->bind();
    texture->bind(textureSlot);
}

}
