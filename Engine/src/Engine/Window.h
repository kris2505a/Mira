#pragma once
#include "Core.h"
#include <SDL_video.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include "Entity.h"

struct WindowProcs {
	unsigned int width;
	unsigned int height;
	bool vSync;

};

class API Window {
private:
	WindowProcs m_procs;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_isRunning;

public:
	Window();
	~Window();
	void renderBind(Entity* entity);
	void clearBg(Uint8 r = 0u, Uint8 g = 0u, Uint8 b = 0u, Uint8 a = 0u);
	void renderAll();
	bool isRunning();
	void close();
};