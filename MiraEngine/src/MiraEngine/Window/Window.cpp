#include <MiraPreCompHeader.h>
#include "Window.h"
#include <SDL.h>
#include <MiraEngine/Logging/Log.h>

Window::Window(const WinProcs& _procs) 
	: m_procs(_procs), m_window(nullptr), m_renderer(nullptr), m_event(SDL_Event()), m_isOpen(true) {
	
	int initResult = SDL_Init(SDL_INIT_EVERYTHING);
	if (!initResult) {
		MIRA_ELOG(ERROR, "Unable to init SDL");
	}
	m_window = SDL_CreateWindow(m_procs.title.c_str(), 200, 200, m_procs.width, m_procs.height, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

Window::~Window() {
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}

unsigned int Window::getWidth() const {
	return m_procs.width;
}

unsigned int Window::getHeight() const {
	return m_procs.height;
}

SDL_Renderer* Window::getRenderer() const {
	return m_renderer;
}

void Window::pollEvents() {
	while (SDL_PollEvent(&m_event)) {
		if (m_event.type == SDL_QUIT)
			m_isOpen = false;
	}
}

bool Window::isOpen() const {
	return m_isOpen;
}