#pragma once
#include "Core.h"
#include "Win32/Window.h"
#include "Renderer/Renderer.h"
#include "WindowAttributes.h"
#include <memory>
#include "Signals/Signal.h"
#include "Layers/LayerStack.h"
#include "Utils/Timer.h"

namespace Mira {

class MIRA_API Engine {
public:
	Engine();
	~Engine();

	void init();
	void shutdown();
	void mainloop();

protected:
	void addLayer(std::unique_ptr <Layer> layer);

private:
	void pulse();
	void render();
	void signal(const Signal& s);

private:
	std::unique_ptr <Window>     m_window;
	std::unique_ptr <Renderer>   m_renderer;
	bool                         m_running;
	WindowAttributes			 m_attrib;
	LayerStack                   m_layerStack;
	Timer						 m_dtClock;
	float						 m_deltaTime;
};

Engine* createApp();

}