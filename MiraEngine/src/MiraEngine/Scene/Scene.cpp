#include <MiraPreCompHeader.h>
#include "Scene.h"

namespace Mira {

uint32_t Scene::m_entityIdGenerator = 0;


Scene::Scene(uint32_t _sceneId, const std::string& _name)
	: m_sceneId(_sceneId), m_name(_name){
	
}

template <typename T, typename... Args>
T& Scene::createEntity(Args&... args) {
	std::shared_ptr <Entity> ent = std::make_shared <T> (std::forward<Args>(args)...);
	ent->p_scene = this;
	ent->m_entityId = m_entityIdGenerator++;
	m_entities.push_back(ent);
	m_transformComponents[ent->m_entityId] = TransformComponent();
	return ent.get();
}

void Scene::update(float deltaTime) {
	for (auto& entity : m_entities)
		entity->update(deltaTime);
}

void Scene::render(Renderer* renderer) {
	for (auto& entity : m_entities)
		entity->render(renderer);
}

std::vector<std::shared_ptr<Entity>>& Scene::getEntities() {
	return m_entities;
}

uint32_t Scene::getId() const {
	return m_sceneId;
}

const std::string& Scene::getName() const {
	return m_name;
}

Scene::~Scene() {
	m_entities.clear();
	m_transformComponents.clear();
}

}//namespace ends