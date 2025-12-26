#include <PreCompHeader.hpp>
#include "LayerStack.hpp"
#include "Logger/Log.hpp"

namespace Mira {

LayerStack::LayerStack() : m_layerInd(0) {
	
}

LayerStack::~LayerStack() {
	for (auto& layer : m_layers) {
		if (layer)
			delete layer;
	}
	m_layers.clear();
}

void LayerStack::addLayer(Layer* layer) {
	m_layers.insert(m_layers.begin() + m_layerInd, layer);
	m_layerInd++;
}

void LayerStack::addUI(Layer* ui) {
	m_layers.push_back(ui);
}

void LayerStack::removeLayer(Layer* layer) {
	auto iter = std::find(m_layers.begin(), m_layers.end(), layer);
	MIRA_ASSERT(iter != m_layers.end(), "Layer not found");
	m_layers.erase(iter);
	m_layerInd--;
}

void LayerStack::removeUI(Layer* ui) {
	auto iter = std::find(m_layers.begin(), m_layers.end(), ui);
	MIRA_ASSERT(iter != m_layers.end(), "Layer not found");
	m_layers.erase(iter);
}

const std::vector<Layer*>& LayerStack::getLayers() const {
	return m_layers;
}

}