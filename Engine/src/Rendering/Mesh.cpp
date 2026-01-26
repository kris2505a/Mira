#include "Mesh.hpp"
#include "Vertex.hpp"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

std::shared_ptr <MeshSharedState> MeshSharedState::s_cubeMesh;

void Mesh::bind() {
    if (auto mesh = m_sharedState.lock()) {
        mesh->m_vbo->bind();
        mesh->m_ibo->bind();
    }
}

unsigned int Mesh::getIndexCount() const {
    if (auto mesh = m_sharedState.lock()) {
        return mesh->m_ibo->indexCount();
    }
    return 0;
}

std::unique_ptr<Mesh> Mesh::createCubeMesh() {
	auto mesh = std::make_unique <Mesh>();
	
	if (MeshSharedState::s_cubeMesh) {
		mesh->m_sharedState = MeshSharedState::s_cubeMesh;
        return mesh;
	}

	MeshSharedState::s_cubeMesh = std::make_shared <MeshSharedState>();

    std::vector<Vertex> vertices = {

        // +Z (Front)
        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {0, 1}},
        {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {0, 0}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1, 0}},
        {{ 0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1, 1}},

        // -Z (Back)
        {{ 0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0, 1}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 0, -1}, {0, 0}},
        {{-0.5f,  0.5f, -0.5f}, {0, 0, -1}, {1, 0}},
        {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 1}},

        // +X (Right)
        {{ 0.5f, -0.5f,  0.5f}, {1, 0, 0}, {0, 1}},
        {{ 0.5f,  0.5f,  0.5f}, {1, 0, 0}, {0, 0}},
        {{ 0.5f,  0.5f, -0.5f}, {1, 0, 0}, {1, 0}},
        {{ 0.5f, -0.5f, -0.5f}, {1, 0, 0}, {1, 1}},

        // -X (Left)
        {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 1}},
        {{-0.5f,  0.5f, -0.5f}, {-1, 0, 0}, {0, 0}},
        {{-0.5f,  0.5f,  0.5f}, {-1, 0, 0}, {1, 0}},
        {{-0.5f, -0.5f,  0.5f}, {-1, 0, 0}, {1, 1}},

        // +Y (Top)
        {{-0.5f,  0.5f,  0.5f}, {0, 1, 0}, {0, 1}},
        {{-0.5f,  0.5f, -0.5f}, {0, 1, 0}, {0, 0}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 1, 0}, {1, 0}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 1, 0}, {1, 1}},

        // -Y (Bottom)
        {{-0.5f, -0.5f, -0.5f}, {0, -1, 0}, {0, 1}},
        {{-0.5f, -0.5f,  0.5f}, {0, -1, 0}, {0, 0}},
        {{ 0.5f, -0.5f,  0.5f}, {0, -1, 0}, {1, 0}},
        {{ 0.5f, -0.5f, -0.5f}, {0, -1, 0}, {1, 1}},
    };

    MeshSharedState::s_cubeMesh->m_vbo = std::make_unique <VertexBuffer>(
        vertices.data(),
        static_cast <unsigned int> (vertices.size()),
        sizeof(Vertex)
    );

    std::vector<uint32_t> indices = {
         0,  1,  2,   0,  2,  3,   // Front
         4,  5,  6,   4,  6,  7,   // Back
         8,  9, 10,   8, 10, 11,   // Right
        12, 13, 14,  12, 14, 15,   // Left
        16, 17, 18,  16, 18, 19,   // Top
        20, 21, 22,  20, 22, 23    // Bottom
    };

    MeshSharedState::s_cubeMesh->m_ibo = std::make_unique <IndexBuffer>(
        indices.data(),
        static_cast <unsigned int> (indices.size())
    );

    mesh->m_sharedState = MeshSharedState::s_cubeMesh;
    return mesh;
}

std::unique_ptr<Mesh> Mesh::createCustomMesh(const std::string& path) {
    auto mesh = std::make_unique <Mesh>();
    auto meshState = std::make_shared <MeshSharedState>(); //exception for custom meshes
    
    std::vector <Vertex> vertices;

    Assimp::Importer importer;  
    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_JoinIdenticalVertices |
        aiProcess_CalcTangentSpace |
        aiProcess_ImproveCacheLocality |
        aiProcess_SortByPType |
        aiProcess_ConvertToLeftHanded
    );

    if (!scene || !scene->mRootNode) {
        std::cout << "Assimp Error: " << importer.GetErrorString() << std::endl;
        std::abort();
    }

    aiMesh* cusMesh = scene->mMeshes[0];

    vertices.reserve(cusMesh->mNumVertices);

    for (size_t i = 0; i < cusMesh->mNumVertices; i++) {
        Vertex v{};
        v.position.x = cusMesh->mVertices[i].x;
        v.position.y = cusMesh->mVertices[i].y;
        v.position.z = cusMesh->mVertices[i].z;

        if (cusMesh->HasNormals()) {
            v.normal.x = cusMesh->mNormals[i].x;
            v.normal.y = cusMesh->mNormals[i].y;
            v.normal.z = cusMesh->mNormals[i].z;
        }

        if (cusMesh->HasTextureCoords(0)) {
            v.uv.x = cusMesh->mTextureCoords[0][i].x;
            v.uv.y = cusMesh->mTextureCoords[0][i].y;
        }
        vertices.push_back(v);
    }

    meshState->m_vbo = std::make_unique <VertexBuffer>(
        vertices.data(), 
        static_cast <unsigned int>(vertices.size()), 
        sizeof(Vertex)
    );

    std::vector <uint32_t> indices;
    indices.reserve(cusMesh->mNumFaces * 3);

    for (size_t i = 0; i < cusMesh->mNumFaces; i++) {
        const aiFace& face = cusMesh->mFaces[i];
        
        for (size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    meshState->m_ibo = std::make_unique <IndexBuffer>(indices.data(), static_cast <unsigned int>(indices.size()));
    mesh->m_sharedState = meshState;
    return mesh;
}
