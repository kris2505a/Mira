#pragma once
#include <vector>
#include "Layer.hpp"

namespace Mira {

class LayerStack {
public:
	LayerStack();
	~LayerStack();
	
	void addLayer(Layer* layer);
	void addUI(Layer* ui);
	void removeLayer(Layer* layer);
	void removeUI(Layer* ui);

	const std::vector <Layer*>& getLayers() const;

private:
	std::vector <Layer*> m_layers;
	int m_layerInd;
};

}