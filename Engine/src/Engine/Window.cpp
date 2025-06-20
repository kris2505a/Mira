#include "Window.h"

Window::Window() : m_window(nullptr), m_renderer(nullptr), m_isRunning(true) {
	m_procs.width = 1600u;
	m_procs.height = 900u;
	m_procs.vSync = false;

	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow(
		"Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_procs.width,
		m_procs.height,
		SDL_WINDOW_SHOWN
	);
	m_renderer = SDL_CreateRenderer(
		m_window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
}

Window::~Window() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::renderBind(Entity* entity) {
	entity->render(m_renderer);
}

void Window::clearBg(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderClear(m_renderer);
}

void Window::renderAll() {
	SDL_RenderPresent(m_renderer);
}

bool Window::isRunning() {
	return m_isRunning;
}


void Window::close() {
	m_isRunning = false;
}