#include <PreCompHeader.hpp>
#include "Mesh.hpp"
#include "Math/Vertex.hpp"

namespace Mira {

Mesh::~Mesh() {
	if (m_vbo)
		delete m_vbo;
	if (m_ibo)
		delete m_ibo;
}

uint32_t Mesh::indexCount() const {
    return m_ibo->indexCount();
}

Mesh* Mesh::cubeMesh() {
	Mesh* mesh = new Mesh;

    Vertex vertices[] = {
        // FRONT (+Z)
        {{-0.5f,  0.5f,  0.5f}},
        {{ 0.5f,  0.5f,  0.5f}},
        {{ 0.5f, -0.5f,  0.5f}},
        {{-0.5f, -0.5f,  0.5f}},

        // BACK (-Z)
        {{ 0.5f,  0.5f, -0.5f}},
        {{-0.5f,  0.5f, -0.5f}},
        {{-0.5f, -0.5f, -0.5f}},
        {{ 0.5f, -0.5f, -0.5f}},

        // LEFT (-X)
        {{-0.5f,  0.5f, -0.5f}},
        {{-0.5f,  0.5f,  0.5f}},
        {{-0.5f, -0.5f,  0.5f}},
        {{-0.5f, -0.5f, -0.5f}},

        // RIGHT (+X)
        {{ 0.5f,  0.5f,  0.5f}},
        {{ 0.5f,  0.5f, -0.5f}},
        {{ 0.5f, -0.5f, -0.5f}},
        {{ 0.5f, -0.5f,  0.5f}},
                              
        // TOP (+Y)           
        {{-0.5f,  0.5f, -0.5f}},
        {{ 0.5f,  0.5f, -0.5f}},
        {{ 0.5f,  0.5f,  0.5f}},
        {{-0.5f,  0.5f,  0.5f}},

        // BOTTOM (-Y)
        {{-0.5f, -0.5f,  0.5f}},
        {{ 0.5f, -0.5f,  0.5f}},
        {{ 0.5f, -0.5f, -0.5f}},
        {{-0.5f, -0.5f, -0.5f}}
    };

    mesh->m_vbo = new VertexBuffer(vertices, sizeof(vertices), sizeof(Vertex));

    uint32_t indices[] = {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };

    mesh->m_ibo = new IndexBuffer(indices, sizeof(indices), std::size(indices));
    return mesh;
}

}