#include <MiraPreCompHeader.h>
#include "LayerStack.h"

namespace Mira {

void LayerStack::pushLayer(Layer* _layer) {
	m_layers.emplace(m_layers.begin() + m_layerIndex, _layer);
	m_layerIndex++;
}

void LayerStack::pushOverlay(Layer* _overlay) {
	m_layers.emplace_back(_overlay);
}

void LayerStack::popLayer(Layer* _layer) {
	auto layer = std::find(m_layers.begin(), m_layers.end(), _layer);
	if (layer != m_layers.end()) {
		m_layers.erase(layer);
		m_layerIndex--;
	}
}

void LayerStack::popOverlay(Layer* _overlay) {
	auto layer = std::find(m_layers.begin(), m_layers.end(), _overlay);
	if (layer != m_layers.end())
		m_layers.erase(layer);
}

LayerStack::~LayerStack() {
	for (auto& layer : m_layers)
		delete layer;
	m_layers.clear();
}

std::vector<Layer*>::iterator LayerStack::begin() {
	return m_layers.begin();
}
std::vector<Layer*>::iterator LayerStack::end() {
	return m_layers.end();
}

} //namespace ends