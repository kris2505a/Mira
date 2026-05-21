#pragma once
#include <vector>
#include "Mira/Core/MemoryType.hpp"
#include "Layer.hpp"

namespace Mira {

class LayerManager {
public:
	LayerManager() = default;
	~LayerManager() = default;

	void addLayer(Scope<Layer> layer);
	void addOverlay(Scope<Layer> overlay);
	
	void removeLayer(const std::string& layerName);
	void removeOverlay(const std::string& overlayName);

	const std::vector<Scope<Layer>>& getLayers() const;

private:
	std::vector<Scope<Layer>> m_layers;
	uint32_t m_layerIndex = 0;
};

}