#pragma once
#include "Mesh.hpp"
#include "Material.hpp"
#include <unordered_map>
#include <string>

#include "Mira/Core/Core.hpp"

namespace Mira {

class MIRA_API RenderResourceManager {
public:
    static Ref<Mesh> createCubeMesh();
    static Ref<Mesh> createQuadMesh();

    //static Ref<Mesh> creteSphereMesh();
    //static Ref<Mesh> createCustomMesh(const std::string& name);

    static Ref<Material> createMaterial(const std::string& materialName, const std::string& shaderName = "Def", const std::string& textureName = "Def");
    // static Ref<Material> createTextureMaterial(const std::string& name);

    static RenderResourceManager& get();

private:
    static Ref<Shader> createShader(const std::string& name);
    static std::shared_ptr<Texture> createTexture(const std::string &name);

private:
    std::unordered_map<std::string, Ref<Mesh>> m_meshMap;
    std::unordered_map<std::string, Ref<Material>> m_materialMap;
    std::unordered_map<std::string, Ref<Texture>> m_textureMap;
    std::unordered_map<std::string, Ref<Shader>> m_shaderMap;
    static RenderResourceManager s_instance;
};

}
