#include <MiraPreCompHeader.h>
#include "Window.h"
#include <SDL.h>
#include <MiraEngine/Logging/Log.h>

//Events
#include <MiraEngine/Event/KeyboardEvent.h>
#include <MiraEngine/Event/MouseEvent.h>
#include <MiraEngine/Event/WindowEvent.h>

namespace Mira {

Window::Window(const WinProcs& _procs)
	: m_procs(_procs), m_window(nullptr), m_isOpen(true), m_event(SDL_Event()) {

	int initResult = SDL_Init(SDL_INIT_VIDEO);
	if (initResult != 0) {
		MIRA_LOG(ERROR, "Unable to init SDL");
	}
	m_window = SDL_CreateWindow(m_procs.title.c_str(), 200, 200, m_procs.width, m_procs.height, SDL_WINDOW_SHOWN);
}

Window::~Window() {
	SDL_DestroyWindow(m_window);
}

unsigned int Window::getWidth() const {
	return m_procs.width;
}

unsigned int Window::getHeight() const {
	return m_procs.height;
}

SDL_Window* Window::getwindow() const {
	return m_window;
}

void Window::pollEvents() {
	while (SDL_PollEvent(&m_event)) {
		switch (m_event.type) {
		
		case SDL_QUIT:
		{
			WindowCloseEvent e;
			m_callback(e);
			m_isOpen = false;
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

} //namespace ends