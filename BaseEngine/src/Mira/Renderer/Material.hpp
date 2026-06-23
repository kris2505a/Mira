#pragma once
#include "RHI/Shader.hpp"
#include "RHI/Texture.hpp"

namespace Mira {

class Material {
    friend class RenderResourceManager;
    friend class AssetManager;
public:
    Material() = default;
    ~Material() = default;
    
    void bind(int textureSlot = 0) const;

private:
    Ref<Shader> shader;
    Ref<Texture> texture;
};

}
