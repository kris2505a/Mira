#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraPreCompHeader.h>
#include <SDL_video.h>
#include <SDL_render.h>

struct WinProcs {
	unsigned int width;
	unsigned int height;
	std::string title;

	WinProcs(unsigned int _width = 1280u, unsigned int _height = 720u, const std::string& _title = "MiraEngine")
		: width(_width), height(_height), title(_title) {}
};

class MIRA_API Window {

public:
	Window(const WinProcs& _procs = WinProcs());

	~Window();

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	SDL_Renderer* getRenderer() const;
	void pollEvents();

private:
	WinProcs m_procs;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event m_event;
	bool m_isOpen;
	bool isOpen() const;
	
};