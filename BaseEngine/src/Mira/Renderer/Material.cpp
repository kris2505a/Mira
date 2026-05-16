#include "MiraPch.h"
#include "Material.h"

namespace Mira {

void Material::bind(int textureSlot) const {
    m_shader->bind();

    if (m_hasTexture) {
        m_texture->bind(textureSlot);
    }
}

bool Material::hasTexture() const {
    return m_hasTexture;
}

}
