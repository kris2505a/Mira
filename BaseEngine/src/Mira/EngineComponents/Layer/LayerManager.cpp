#include "MiraPch.hpp"
#include "LayerManager.hpp"

namespace Mira {

void LayerManager::addLayer(Layer* layer) {
	m_layers.emplace(m_layers.begin() + m_layerIndex, layer);
	m_layerIndex++;
}

void LayerManager::addOverlay(Layer* overlay) {
	m_layers.emplace_back(overlay);
}

void LayerManager::removeLayer(const std::string& name) {
	auto iter = std::find_if(m_layers.begin(), m_layers.end(), [name](const auto& layer) {
		return name == layer->getLayerName();
	});

	if (iter != m_layers.end()) {
		(*iter)->detach();
		delete* iter;
		m_layers.erase(iter);
		m_layerIndex--;
	}
}

void LayerManager::removeOverlay(const std::string& name) {
	auto iter = std::find_if(m_layers.begin(), m_layers.end(), [name](const auto& layer) {
		return name == layer->getLayerName();
	});

	if (iter != m_layers.end()) {
		(*iter)->detach();
		delete *iter;
		m_layers.erase(iter);
	}
}

const std::vector<Layer*>& LayerManager::getLayers() const {
	return m_layers;
}

LayerManager::~LayerManager() {
	for (auto* layer : m_layers) {
		if (layer) {
			delete layer;
		}
	}

	m_layers.clear();
}

}