#include <PreCompHeader.hpp>
#include "DbgCube.hpp"
#include "Renderer/Renderer.hpp"

namespace Mira {

DbgCube::DbgCube(Material* material, Mesh* mesh, Camera* camera)
	: m_material(material), m_mesh(mesh), p_camera(camera) {

	m_transform = new Transform;

	dx::XMMATRIX mat = dx::XMMatrixTranspose(
		m_transform->model() * p_camera->view() * p_camera->projection()
		
	);

	m_color = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_ccbo = new ConstantBuffer(&m_color, sizeof(m_color), ShaderType::PixelShader);

	m_cbo = new ConstantBuffer(&mat, sizeof(mat), ShaderType::VertexShader);
}

DbgCube::~DbgCube() {
	if (m_cbo)
		delete m_cbo;
	if (m_transform)
		delete m_transform;
}

Transform* DbgCube::transform() {
	return m_transform;
}

void DbgCube::render() {
	m_mesh->bind();
	m_material->bind();
	m_ccbo->bind();
	m_cbo->bind();

	Renderer::s_instance->indexedRender(36);
}

void DbgCube::pulse(float deltaTime) {
	
	dx::XMMATRIX mvp = dx::XMMatrixTranspose(
		m_transform->model() * p_camera->view() * p_camera->projection()
	);
	


	
	m_ccbo->update(&m_color, sizeof(m_color));
	m_cbo->update(&mvp, sizeof(mvp));
}


}