#include <MiraPreCompHeader.h>
#include "Layer.h"

namespace Mira {

Layer::Layer(const std::string& name) : m_layerName(name) {

}

Layer::~Layer() {

}

const std::string& Layer::getLayerName() const {
	return m_layerName;
}

}