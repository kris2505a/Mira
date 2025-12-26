#include <PreCompHeader.hpp>
#include "Scene.hpp"

namespace Mira {

Scene::Scene(uint32_t id)
	: m_sceneId(id), m_initialized (false) {

}

void Scene::render() {

}

void Scene::spark() {

}

void Scene::pulse(float deltaTime) {

}

void Scene::init() {
	m_initialized = true;
	spark();
}

void Scene::shutdown() {
	for (auto& entity : m_entities) {
		if (entity)
			delete entity;
	}
	m_entities.clear();
	m_initialized = false;
}

Scene::~Scene() {
	if (m_initialized) {
		shutdown();
	}
}

}