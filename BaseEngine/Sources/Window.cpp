#include <Window/Window.hpp>
#include <stdexcept>
#include <Events/Event.hpp>

namespace Mira {

Window::Window(unsigned int width, unsigned int height, const std::string& title) 
		: m_width(width), m_height(height), m_title(title) {

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		throw std::runtime_error("Unable to Init SDL!");
	}
	
	m_window = SDL_CreateWindow(
		m_title.c_str(),
		static_cast <int> (m_width),
		static_cast <int> (m_height),
		SDL_WINDOW_RESIZABLE
	);

}

Window::~Window() {
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::pollEvents() {
	while (SDL_PollEvent(&m_event)) {
		switch (m_event.type) {
		case SDL_EVENT_QUIT:
			Event e(EventType::WindowClosed);
			break;


		}

	}
}

}