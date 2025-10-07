#include <MiraPreCompHeader.h>
#include "Layer.h"

namespace Mira {

Layer::Layer(const std::string& name) : m_layerName(name) {

}

Layer::~Layer() {

}

void Layer::render() {

}

void Layer::update(float deltaTime) {

}

void Layer::event(Event& e) {

}

const std::string& Layer::getLayerName() const {
	return m_layerName;
}

}