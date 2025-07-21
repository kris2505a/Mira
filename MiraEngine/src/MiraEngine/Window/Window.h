#pragma once
#include <MiraEngine/Core/MiraCore.h>
#include <MiraEngine/Event/Event.h>
#include <MiraPreCompHeader.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_events.h>
#include <functional>

namespace Mira {

struct MIRA_API WinProcs {
	unsigned int width;
	unsigned int height;
	std::string title;

	WinProcs(unsigned int _width = 1280u, unsigned int _height = 720u, const std::string& _title = "MiraEngine")
		: width(_width), height(_height), title(_title) {
	}
};

class MIRA_API Window {

	using eventCallbackFn = std::function<void(Mira::Event&)>;

public:
	Window(const WinProcs& _procs = WinProcs());

	~Window();

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	void pollEvents();
	bool isOpen() const;
	void setCallbackFn(const eventCallbackFn& fn);
	SDL_Window* getwindow() const;

private:
	WinProcs m_procs;
	SDL_Window* m_window;
	SDL_Event m_event;
	bool m_isOpen;
	eventCallbackFn m_callback;

};

}