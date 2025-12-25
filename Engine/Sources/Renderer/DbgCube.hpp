#pragma once
#include "Core/Core.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "InputLayout.hpp"
#include "Math/Vertex.hpp"
#include "ConstantBuffer.hpp"

namespace Mira {

namespace dx = DirectX;

class MIRA_API DbgCube {
public:
	DbgCube() {
		Vertex vertices[] = {
			{{ -0.5f, -0.5f, 0.0f }}, // bottom-left
			{{ -0.5f,  0.5f, 0.0f }}, // top-left
			{{  0.5f,  0.5f, 0.0f }}, // top-right
			{{  0.5f, -0.5f, 0.0f }}  // bottom-right
		};

		uint32_t indices[] = {
			0, 1, 2, 0, 2, 3
		};

		m_vbo = new VertexBuffer(vertices, sizeof(vertices), sizeof(Vertex));
		m_ibo = new IndexBuffer(indices, sizeof(indices), std::size(indices));
		m_shader = new Shader(L"Shaders/VertexShader.cso", L"Shaders/PixelShader.cso");
		m_ilo = new InputLayout(m_shader->blobs());
		m_ilo->addLayout({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		m_ilo->createLayout();
		
		auto rad = [](float deg) { return deg * dx::XM_PI / 180.0f; };

		dx::XMMATRIX model = dx::XMMatrixTranspose(
			dx::XMMatrixScaling(9.0f / 16.0f, 1.0f, 0.0f)
		);
		m_cbo = new ConstantBuffer(&model, sizeof(model), ShaderType::VertexShader);
		
	}

	void bind() const {
		m_vbo->bind();
		m_ibo->bind();
		m_shader->bind();
		m_ilo->bind();
		m_cbo->bind();
	}

	~DbgCube() {
		if (m_vbo) 
			delete m_vbo;
		if (m_ibo)
			delete m_ibo;
		if (m_shader)
			delete m_shader;
		if (m_ilo)
			delete m_ilo;
		if (m_cbo)
			delete m_cbo;
	}

private:
	VertexBuffer* m_vbo;
	IndexBuffer* m_ibo;
	Shader* m_shader;
	InputLayout* m_ilo;
	ConstantBuffer* m_cbo;
};

}