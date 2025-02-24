#pragma once

#include "Cyan/core.hpp"
#include "Layer.hpp"

#include <vector>

namespace Cyan {
	
	class CYANAPI LayerStack {

	private:
		std::vector <Layer*> m_layers;
		int m_layerInsert;

	public:

		LayerStack();
		~LayerStack();
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overLay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		const int end() { return m_layers.size() - 1; }
		const std::vector <Layer*>& getLayers() const { return m_layers; }
	};
}