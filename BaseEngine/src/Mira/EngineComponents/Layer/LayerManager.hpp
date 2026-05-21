#pragma once
#include <vector>
#include "Mira/Core/MemoryType.hpp"
#include "Mira/Core/Core.hpp"
#include "Layer.hpp"

namespace Mira {

class MIRA_API LayerManager {
public:
	LayerManager() = default;
	~LayerManager();

	void addLayer(Layer* layer);
	void addOverlay(Layer* overlay);
	
	void removeLayer(const std::string& layerName);
	void removeOverlay(const std::string& overlayName);

	const std::vector<Layer*>& getLayers() const;

private:
	std::vector<Layer*> m_layers;
	uint32_t m_layerIndex = 0;
};

}