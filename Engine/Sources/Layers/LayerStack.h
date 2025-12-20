#pragma once
#include <memory>
#include <vector>
#include "Layer.h"

namespace Mira {

class LayerStack {
public:
	LayerStack();
	~LayerStack();
	
	void addLayer(std::unique_ptr <Layer> layer);
	void addUI(std::unique_ptr <Layer> ui);
	void removeLayer(Layer* layer);
	void removeUI(Layer* ui);

	const std::vector <std::unique_ptr<Layer>>& getLayers() const;

private:
	std::vector < std::unique_ptr<Layer>> m_layers;
	int m_layerInd;
};

}