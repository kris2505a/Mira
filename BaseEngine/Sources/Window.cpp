#include <Window/Window.hpp>
#include <stdexcept>
#include <Events/Event.hpp>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_properties.h>

namespace Mira {

Window::Window(EventSystem& es, unsigned int width, unsigned int height, const std::string& title) 
		: r_eventSystem(es), m_width(width), m_height(height), m_title(title) {

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

HWND Window::getHandle() {
	SDL_PropertiesID props = SDL_GetWindowProperties(m_window);

	return static_cast<HWND>(
		SDL_GetPointerProperty(
			props,
			SDL_PROP_WINDOW_WIN32_HWND_POINTER,
			nullptr
		)
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
			r_eventSystem.pushEvent(e);
			break;

		}

	}
}

}