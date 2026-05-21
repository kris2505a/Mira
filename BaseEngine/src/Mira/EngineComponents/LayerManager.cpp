#include "MiraPch.hpp"
#include "LayerManager.hpp"

namespace Mira {

void LayerManager::addLayer(Scope<Layer> layer) {
	m_layers.emplace(m_layers.begin() + m_layerIndex, std::move(layer));
	m_layerIndex++;
}

void LayerManager::addOverlay(Scope<Layer> overlay) {
	m_layers.emplace_back(std::move(overlay));
}

void LayerManager::removeLayer(const std::string& name) {
	auto iter = std::find_if(m_layers.begin(), m_layers.end(), [name](const Scope<Layer>& layer) {
		return name == layer->getLayerName();
	});

	if (iter != m_layers.end()) {
		m_layers.erase(iter);
		m_layerIndex--;
	}
}

void LayerManager::removeOverlay(const std::string& name) {
	auto iter = std::find_if(m_layers.begin(), m_layers.end(), [name](const Scope<Layer>& layer) {
		return name == layer->getLayerName();
	});

	if (iter != m_layers.end()) {
		m_layers.erase(iter);
	}
}

const std::vector<Scope<Layer>>& LayerManager::getLayers() const {
	return m_layers;
}

}