#include <MiraPreCompHeader.h>
#include "Layer.h"


namespace Mira {

uint32_t Layer::s_idGenerator = 0;

void Layer::onAttach() {
	m_scene = std::make_unique <Scene>(s_idGenerator++, "Mira Scene");
}

void Layer::onDetach() {
	
}

Scene* Layer::getCurrentScene() const {
	return m_scene.get();
}


void Layer::onUpdate(float deltaTime) {
	m_scene->onUpdate(deltaTime);
}

void Layer::onRender(Renderer* renderer) {
	m_scene->onRender(renderer);
}

void Layer::onEvent(Event& e) {
	if (e.getType() == EventType::windowClose)
		MIRA_LOG(INFO, "Window Close");
}

} //namespace ends