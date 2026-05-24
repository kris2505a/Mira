#include "MiraPch.hpp"
#include "RenderResourceManager.hpp"
#include "Vertex.hpp"

namespace Mira {
RenderResourceManager RenderResourceManager::s_instance;

RenderResourceManager& RenderResourceManager::get() {
    return s_instance;
}



Ref<Mesh> RenderResourceManager::createCubeMesh() {
    
    if (get().m_meshMap.count("Cube")) {
        return get().m_meshMap["Cube"];
    }

    auto cubeMesh = createRef<Mesh>();
    
    std::vector<Vertex> vertices = {
        // FRONT
        {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},

        // BACK
        {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},

        // LEFT
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},

        // RIGHT
        {{ 0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},

        // TOP
        {{-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},

        // BOTTOM
        {{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},
    };

    std::vector<uint32_t> indices = {

         0, 1, 2,  2, 3, 0,        // FRONT
         4, 5, 6,  6, 7, 4,        // BACK
         8, 9,10, 10,11, 8,        // LEFT
        12,13,14, 14,15,12,        // RIGHT
        16,17,18, 18,19,16,        // TOP
        20,21,22, 22,23,20         // BOTTOM
    };

    cubeMesh->m_vertexBuffer = VertexBuffer::create(vertices.data(), static_cast<int>(vertices.size()), sizeof(Vertex));
    cubeMesh->m_indexBuffer = IndexBuffer::create(indices.data(), static_cast<int>(indices.size()));

    get().m_meshMap["Cube"] = cubeMesh;

    return cubeMesh;
}

Ref<Mesh> RenderResourceManager::createQuadMesh() {
    if (get().m_meshMap.contains("Quad")) {
        return get().m_meshMap["Quad"];
    }

    auto quadMesh = createRef<Mesh>();
    
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f,  0.0f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.0f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.0f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.0f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}}
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,
        2, 3, 0
    };

    quadMesh->m_vertexBuffer = VertexBuffer::create(vertices.data(), static_cast<int>(vertices.size()), sizeof(Vertex));
    quadMesh->m_indexBuffer = IndexBuffer::create(indices.data(), static_cast<int>(indices.size()));

    get().m_meshMap["Quad"] = quadMesh;

    return quadMesh;
}

Ref<Material> RenderResourceManager::createMaterial(const std::string& materialName, const std::string& shaderName, const std::string& textureName) {
    if (get().m_materialMap.contains(materialName)) {
        return get().m_materialMap[materialName];
    }

    auto shader = createShader(shaderName);
    auto texture = createTexture(textureName);

    auto mat = createRef<Material>();
    mat->m_shader = shader;
    mat->m_texture = texture;

    get().m_materialMap[materialName] = mat;

    return mat;
}

Ref<Shader> RenderResourceManager::createShader(const std::string &name) {
    if (get().m_shaderMap.contains(name)) {
        return get().m_shaderMap[name];
    }

    InputLayout layout;
    layout.addLayout({
        "POSITION",
        LayoutDataType::Float,
        3
    });

    layout.addLayout({
        "NORMAL",
        LayoutDataType::Float,
        3
    });

    layout.addLayout({
        "TEXCOORD",
        LayoutDataType::Float,
        2
    });

    auto shader = Shader::create(std::wstring(name.begin(), name.end()), layout);
    get().m_shaderMap[name] = shader;
    return shader;
}

std::shared_ptr<Texture> RenderResourceManager::createTexture(const std::string &name) {
    if (get().m_textureMap.contains(name)) {
        return get().m_textureMap[name];
    }

    Ref<Texture> texture;

    if (name == "Def") {
        texture = Texture::create();
    }
    else {
        std::string path = "texture/" + name;
        texture = Texture::create(path);
    }

    get().m_textureMap[name] = texture;
    return texture;
}
}
