#include <PreCompHeader.hpp>
#include "Cube.hpp"

namespace Mira {

void Cube::spark() {

}

void Cube::pulse(float deltaTime) {

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

void Cube::render(const Renderer* renderer) {
	
}

TransformComponent* Cube::transformComponent() {
	return m_transformComp;
}

}