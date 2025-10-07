#pragma once
#include <Base/MiraAPI.h>
#include <Win32/Win32Window.h>
#include <Events/Event.h>
#include <memory>
#include <EngineComponents/LayerStack.h>

namespace Mira {

class MIRA_API Engine {
public:
	Engine();
	~Engine();

	void run();

private:

	void update();
	void render();
	void event(Event& e);

private:
	std::unique_ptr <Win32Window> m_window;
	LayerStack m_layerStack;
};

}