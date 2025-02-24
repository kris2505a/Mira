#include "PreCompHeaders.hpp"
#include "LayerStack.hpp"

namespace Cyan{
	LayerStack::LayerStack() {
		m_layerInsert = 0;
	}

	LayerStack::~LayerStack() {

		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer) {
		m_layers.emplace(m_layers.begin() + m_layerInsert, layer);
		m_layerInsert++;
	}

	void LayerStack::pushOverlay(Layer* overLay) {
		m_layers.emplace_back(overLay);
	}

	void LayerStack::popLayer(Layer* layer) {
		auto iter = std::find(m_layers.begin(), m_layers.end(), layer);

		if (iter != m_layers.end()) {
			m_layers.erase(iter);
			m_layerInsert--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay) {
		auto iter = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (iter != m_layers.end()) {
			m_layers.erase(iter);
		}

	}
}
