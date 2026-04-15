#pragma once
#include <Core/Core.hpp>
#include <SDL3/SDL.h>
#include <string>
#include <Events/EventSystem.hpp>
#include <Windows.h>

namespace Mira {

class Window {
public:
	Window(EventSystem& es, unsigned int width = 1280u, unsigned int height = 720u, const std::string& title = "Engine");
	~Window();
	HWND getHandle();
	void pollEvents();

private:
	SDL_Window* m_window	= nullptr;
	SDL_Event m_event		= {};
	unsigned int m_width	= 1280u;
	unsigned int m_height	= 720u;
	std::string m_title		= "";
	EventSystem& r_eventSystem;
};

}