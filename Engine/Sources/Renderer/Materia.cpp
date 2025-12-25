#include <PreCompHeader.hpp>
#include "Material.hpp"

namespace Mira {

Material::~Material() {
	if (m_layout)
		delete m_layout;
	if (m_shader)
		delete m_shader;
}

Material* Material::createMaterial() {
	Material* material = new Material;
	material->m_shader = new Shader(L"Shaders/VertexShader.cso", L"Shaders/PixelShader.cso");
	material->m_layout = new InputLayout(material->m_shader->blobs());
	material->m_layout->addLayout({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	material->m_layout->createLayout();
	return material;
}

}