#pragma once
#include <Base/MiraAPI.h>
#include <Window/Window.h>
#include <Events/Event.h>

namespace Mira {

class MIRA_API Engine {
public:
	Engine();
	~Engine();

	void run();

private:
	void init();
	void shutdown();

	void update();
	void render();
	void event(Event& e);

private:
	std::unique_ptr <WindowBase> m_window;
};

}