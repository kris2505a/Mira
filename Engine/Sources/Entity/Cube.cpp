#include <PreCompHeader.hpp>
#include "Cube.hpp"
#include "Renderer/Renderer.hpp"
#include "imgui.h"

namespace Mira {

Cube::Cube(Camera* camera) {
	m_transformComp = new TransformComponent;
	m_renderComp = new RenderComponent;
	p_camera = camera;

	auto mvp = dx::XMMatrixTranspose(m_transformComp->model() * p_camera->view() * p_camera->projection());

	m_vcbo = new ConstantBuffer(&mvp, sizeof(mvp), ShaderType::VertexShader);
}

Cube::~Cube() {
	delete m_transformComp;
	delete m_renderComp;
	delete m_vcbo;
}

void Cube::spark() {
	m_renderComp->material->color({ 1.0f, 0.0f, 1.0f, 1.0f });
}

void Cube::renderUI() {
	ImGui::Begin("Cube");

	ImGui::InputFloat("X Pos: ", &m_transformComp->position.x);
	ImGui::InputFloat("Y Pos: ", &m_transformComp->position.y);
	ImGui::InputFloat("Z Pos: ", &m_transformComp->position.z);


	ImGui::InputFloat("X Rot: ", &m_transformComp->rotation.x);
	ImGui::InputFloat("Y Rot: ", &m_transformComp->rotation.y);
	ImGui::InputFloat("Z Rot: ", &m_transformComp->rotation.z);


	ImGui::End();
}

void Cube::pulse(float deltaTime) {
	auto mvp = dx::XMMatrixTranspose(m_transformComp->model() * p_camera->view() * p_camera->projection());
	m_vcbo->update(&mvp, sizeof(mvp));
}

RenderComponent* Cube::renderComponent() const {
	return m_renderComp;
}

void Cube::setMesh(Mesh* mesh) {
	m_renderComp->mesh = mesh;
}

void Cube::setMaterial(Material* material) {
	m_renderComp->material = material;
}

void Cube::render(Renderer* renderer) {
	m_renderComp->mesh->bind();
	m_renderComp->material->bind();
	m_vcbo->bind();
	renderer->indexedRender(m_renderComp->mesh->indexCount());
}

TransformComponent* Cube::transformComponent() {
	return m_transformComp;
}

}