#include <MiraPreCompHeader.h>
#include "Window.h"
#include <SDL.h>
#include <MiraEngine/Logging/Log.h>

//Events
#include <MiraEngine/Event/KeyboardEvent.h>
#include <MiraEngine/Event/MouseEvent.h>

namespace Mira {

Window::Window(const WinProcs& _procs)
	: m_procs(_procs), m_window(nullptr), m_renderer(nullptr), m_isOpen(true), m_event(SDL_Event()) {

	int initResult = SDL_Init(SDL_INIT_VIDEO);
	if (initResult != 0) {
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
		switch (m_event.type) {
		
		case SDL_QUIT:
		{
			m_isOpen = false;
			//EVENT TO BE CREATED FOR CLOSE
		}	break;

		case SDL_KEYDOWN:
		{
			KeyPressedEvent e(m_event.key.keysym.sym, m_event.key.repeat);
			m_callback(e);
		}	break;

		case SDL_KEYUP:
		{
			KeyReleasedEvent e(m_event.key.keysym.sym);
			m_callback(e);
		}	break;

		case SDL_MOUSEMOTION:
		{
			MouseMovedEvent e(m_event.motion.x, m_event.motion.y);
			m_callback(e);
		}	break;

		case SDL_MOUSEBUTTONDOWN:
		{
			MouseButtonPressedEvent e(m_event.button.button);
			m_callback(e);
		}	break;

		case SDL_MOUSEBUTTONUP:
		{
			MouseButtonReleasedEvent e(m_event.button.button);
			m_callback(e);
		}	break;

		case SDL_MOUSEWHEEL:
		{
			MouseScrolledEvent e(m_event.wheel.x, m_event.wheel.y);
			m_callback(e);
		}	break;
		}
	}
}

bool Window::isOpen() const {
	return m_isOpen;
}

void Window::setCallbackFn(const eventCallbackFn& fn) {
	m_callback = fn;
}



}