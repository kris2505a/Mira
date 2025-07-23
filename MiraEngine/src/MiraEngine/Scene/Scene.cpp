#include <MiraPreCompHeader.h>
#include "Scene.h"

namespace Mira {

Scene::Scene(uint32_t _sceneId, const std::string& _name)
	: m_sceneId(_sceneId), m_name(_name){
	
}

template <typename T, typename... Args>
T& Scene::createEntity(Args&... args) {
	std::shared_ptr <Entity> ent = std::make_shared <T> (std::forward<Args>(args)...);
	m_entities.push_back(ent);
	return *ent;
}

void Scene::onUpdate(float deltaTime) {

}

void Scene::onRender(Renderer* renderer) {

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
}

}//namespace ends