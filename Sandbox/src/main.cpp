#include "MiraEngine.hpp"

class Sandbox : public Mira::Engine {
public:
	Sandbox() {
		getLayerManager().addLayer(Mira::Layer::createLayer<Mira::ImGuiLayer>());
	}

	~Sandbox() = default;
};

Mira::Engine* Mira::createApp() {
	return new Sandbox;
}
