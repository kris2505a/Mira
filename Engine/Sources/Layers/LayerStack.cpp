#include <PreCompHeader.h>
#include "LayerStack.h"
#include "Logger/Log.h"

namespace Mira {

LayerStack::LayerStack() : m_layerInd(0) {
	
}

LayerStack::~LayerStack() {

}

void LayerStack::addLayer(std::unique_ptr<Layer> layer) {
	m_layers.insert(m_layers.begin() + m_layerInd, std::move(layer));
	m_layerInd++;
}

void LayerStack::addUI(std::unique_ptr<Layer> ui) {
	m_layers.push_back(std::move(ui));
}

void LayerStack::removeLayer(Layer* layer) {
	auto iter = std::find_if(m_layers.begin(), m_layers.end(),
		[layer](const std::unique_ptr <Layer>& ptr) {
			return ptr.get() == layer;
		}
	);
	MIRA_ASSERT(iter == m_layers.end(), "Layer not found");
	m_layers.erase(iter);
	m_layerInd--;
}

void LayerStack::removeUI(Layer* ui) {
	auto iter = std::find_if(m_layers.begin(), m_layers.end(),
		[ui](const std::unique_ptr <Layer>& ptr) {
			return ptr.get() == ui;
		}
	);
	MIRA_ASSERT(iter == m_layers.end(), "Layer not found");
	m_layers.erase(iter);
}

const std::vector<std::unique_ptr<Layer>>& LayerStack::getLayers() const {
	return m_layers;
}

}