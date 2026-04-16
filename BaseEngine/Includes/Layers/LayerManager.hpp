#pragma once
#include <vector>
#include <memory>
#include "Layer.hpp"

namespace Mira {

class LayerManager {
public:
    LayerManager() = default;
    ~LayerManager() = default;

    void addLayer(std::unique_ptr<Layer> layer, bool overlay = false);
    void removeLayer(Layer* layer);
    Layer* getLayerByName(const std::string& name);
    
    const std::vector<std::unique_ptr<Layer>>& getLayers() const;

private:
    std::vector<std::unique_ptr<Layer>> m_layers;
};

}
