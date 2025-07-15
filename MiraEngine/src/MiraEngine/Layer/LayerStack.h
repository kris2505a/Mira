#pragma once
#include "Layer.h"
#include <MiraEngine/Core/MiraCore.h>
#include <vector>

namespace Mira {

class MIRA_API LayerStack {
public:
	void pushLayer(Layer* _layer);
	void pushOverlay(Layer* _overlay);
	void popLayer(Layer* _layer);
	void popOverlay(Layer* _overlay);

	LayerStack() = default;
	~LayerStack();

	std::vector<Layer*>::iterator begin();
	std::vector<Layer*>::iterator end();


private:
	std::vector <Layer*> m_layers;
	unsigned int m_layerIndex = 0;
};

} //Namespace ends