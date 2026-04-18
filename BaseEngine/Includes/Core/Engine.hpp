#pragma once
#include "Core.hpp"
#include <Events/Event.hpp>
#include <Window/Window.hpp>
#include <RenderAPI.hpp>
#include <GraphicsFactory.hpp>
#include <memory>
#include <Layers/LayerManager.hpp>

namespace Mira {

class MIRA_API Engine {
public:
	Engine();
	~Engine();
	void run();
    void addLayer(std::unique_ptr<Layer> layer);

private:
	void init();
	void cleanup();
	void mainLoop();
	void update();
	void render();
	void handleEvent(Event& e);

private:
	bool m_running                      = true;
	std::unique_ptr<Window> m_window    = nullptr;
    LayerManager m_layerManager         = {};

	std::unique_ptr<mr::RenderAPI> m_renderAPI;
	std::unique_ptr<mr::GraphicsFactory> m_graphicsFactory;
};

}
