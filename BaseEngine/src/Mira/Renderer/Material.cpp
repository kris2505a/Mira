#include "MiraPch.hpp"
#include "Material.hpp"

namespace Mira {

void Material::bind(int textureSlot) const {
    m_shader->bind();
    m_texture->bind(textureSlot);
}

}
