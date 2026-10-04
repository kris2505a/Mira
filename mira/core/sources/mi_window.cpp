#include "core/mi_window.hpp"

MI_CORE

auto Window::create() -> std::expected<Scope<Window>, std::string> {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return std::unexpected{ SDL_GetError() };
    }

    Scope<Window> window = createScope<Window>();

    window->m_nativeWindow = SDL_CreateWindow(
        window->m_WindowTitle.c_str(), 
        window->m_width, 
        window->m_height, 
        SDL_WINDOW_VULKAN
    );

    if (!window->m_nativeWindow) {
        return std::unexpected{ SDL_GetError() };
    }

    return std::move(window);
}

auto Window::pollEvents() -> bool {
    while (SDL_PollEvent(&m_event)) {
        if (SDL_EVENT_QUIT == m_event.type) {
            return false;
        }
    }
    return true;
}

Window::~Window() {
    if (m_nativeWindow) {
        SDL_DestroyWindow(m_nativeWindow);
    }
    SDL_Quit();
}

MI_CORE_END