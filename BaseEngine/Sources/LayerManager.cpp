#include <Layers/LayerManager.hpp>
#include <stdexcept>
#include <algorithm>

namespace Mira {

void LayerManager::addLayer(std::unique_ptr<Layer> layer, bool overlay) {
    if(overlay) {
        m_layers.emplace(m_layers.begin(), std::move(layer));
        return;
    }

    m_layers.push_back(std::move(layer));
}

void LayerManager::removeLayer(Layer* layer) {
    auto iter = std::find_if(m_layers.begin(), m_layers.end(), [layer](const auto& l){
        return l.get() == layer;
    });

    if(iter != m_layers.end()) {
        m_layers.erase(iter);
    }
}

Layer* LayerManager::getLayerByName(const std::string& name) {
    auto iter = std::find_if(m_layers.begin(), m_layers.end(), [name](const auto& layer){
        return layer->getLayerName() == name;
    });
    
    if (iter == m_layers.end()) {
        throw std::runtime_error("Unable to fetch layer!");
    }
    
    return iter->get();
}

const std::vector<std::unique_ptr<Layer>>& LayerManager::getLayers() const {
    return  m_layers;
}


}
