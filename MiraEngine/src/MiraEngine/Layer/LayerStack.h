#pragma once
#include "Layer.h"
#include <MiraEngine/Core/MiraCore.h>
#include <vector>

namespace Mira {

class MIRA_API LayerStack {
public:
	void pushLayer(Layer* layer);
	void pushOverlay(Layer* overlay);
	void popLayer(Layer* layer);
	void popOverlay(Layer* overlay);

	LayerStack() = default;
	~LayerStack();

	std::vector<Layer*>::iterator begin();
	std::vector<Layer*>::iterator end();


private:
	std::vector <Layer*> m_layers;
	unsigned int m_layerIndex = 0;
};

} //Namespace ends