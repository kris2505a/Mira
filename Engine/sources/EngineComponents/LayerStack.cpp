#include <MiraPreCompHeader.h>
#include "LayerStack.h"

namespace Mira {

void LayerStack::addLayer(std::unique_ptr <Layer>& layer) {
	m_layers.insert(m_layers.begin() + m_layerIndex, std::move(layer));
}

void LayerStack::addUI(std::unique_ptr <Layer>& ui) {
	m_layers.push_back(ui);
}

void LayerStack::removeLayer(std::unique_ptr <Layer>& layer) {
	auto iter = std::find_if(m_layers.begin(), m_layers.end(), 
		[&layer](const std::unique_ptr<Layer>& l) { return l.get() == layer.get(); });
	if (iter != m_layers.end()) {
		m_layers.erase(iter);
		m_layerIndex--;
	}
}

void LayerStack::removeUI(std::unique_ptr <Layer>& ui) {
	auto iter = std::find_if(m_layers.begin(), m_layers.end(),
		[&ui](const std::unique_ptr<Layer>& u) { return u.get() == ui.get(); });
	if (iter != m_layers.end())
		m_layers.erase(iter);
}

const std::vector<std::unique_ptr<Layer>>& LayerStack::getLayers() const {
	return m_layers;
}

}