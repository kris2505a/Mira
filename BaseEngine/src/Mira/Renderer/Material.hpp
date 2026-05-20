#pragma once
#include "RHI/Shader.hpp"
#include "RHI/Texture.hpp"

namespace Mira {

class Material {
    friend class InstanceManager;
public:
    Material() = default;
    ~Material() = default;
    
    void bind(int textureSlot = 0) const;
    bool hasTexture() const;

private:
    Scope<Shader> m_shader;
    Scope<Texture> m_texture;
    bool m_hasTexture;
};

}
