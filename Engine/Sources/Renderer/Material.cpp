#include <PreCompHeader.hpp>
#include "Material.hpp"

namespace Mira {

Material::~Material() {
	if (m_layout)
		delete m_layout;
	if (m_shader)
		delete m_shader;
	if (m_pcbo)
		delete m_pcbo;
}

Material* Material::createMaterial() {
	Material* material = new Material;
	material->m_shader = new Shader(L"Shaders/VertexShader.cso", L"Shaders/PixelShader.cso");
	material->m_layout = new InputLayout(material->m_shader->blobs());
	material->m_defaultColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	material->m_pcbo = new ConstantBuffer(&material->m_defaultColor, 4 * sizeof(float), ShaderType::PixelShader);
	
	material->m_layout->addLayout({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	material->m_layout->createLayout();
	return material;
}

void Material::color(const DirectX::XMFLOAT4& color) {
	m_pcbo->update(&color, sizeof(color));
}

}