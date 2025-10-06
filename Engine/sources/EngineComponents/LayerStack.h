#pragma once
#include "Layer.h"
#include <Base/MiraAPI.h>
#include <vector>
#include <memory>

namespace Mira {

class LayerStack {
public:
	LayerStack() = default;
	~LayerStack() = default;

	void addLayer(std::unique_ptr <Layer>& layer);
	void addUI(std::unique_ptr <Layer>& ui);
	void removeLayer(std::unique_ptr <Layer>& layer);
	void removeUI(std::unique_ptr <Layer>& ui);

	const std::vector<std::unique_ptr<Layer>>& getLayers() const;

private:
	std::vector <std::unique_ptr<Layer>> m_layers;
	int m_layerIndex = 0;
};

}