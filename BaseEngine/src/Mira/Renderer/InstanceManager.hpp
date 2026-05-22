#pragma once
#include "Mesh.hpp"
#include "Material.hpp"
#include <unordered_map>
#include <string>

#include "Mira/Core/Core.hpp"

namespace Mira {

class MIRA_API InstanceManager {
public:
    static Ref<Mesh> createCubeMesh();
    static Ref<Mesh> createQuadMesh();

    //static Ref<Mesh> creteSphereMesh();
    //static Ref<Mesh> createCustomMesh(const std::string& name);

    static Ref<Material> createMaterial(const std::string& name);
    // static Ref<Material> createTextureMaterial(const std::string& name);


    static InstanceManager& get();

private:
    std::unordered_map<std::string, Ref<Mesh>> m_meshMap;
    std::unordered_map<std::string, Ref<Material>> m_materialMap;
    static InstanceManager s_instance;
};

}
