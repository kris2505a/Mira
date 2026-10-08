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

        switch (m_event.type) {
        case SDL_EVENT_KEY_DOWN: {
            if (m_callbacks.key) {
                m_callbacks.key(m_event.key.scancode, m_event.key.repeat, true);
            }
            break;
        }

        case SDL_EVENT_KEY_UP: {
            if (m_callbacks.key) {
                m_callbacks.key(m_event.key.scancode,  m_event.key.repeat, false);
            }
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            if (m_callbacks.mouseButton) {
                m_callbacks.mouseButton(m_event.button.button, true);
            }
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP: {
            if (m_callbacks.mouseButton) {
                m_callbacks.mouseButton(m_event.button.button, false);
            }

            break;
        }

        case SDL_EVENT_MOUSE_MOTION: {
            if (m_callbacks.mouseMove) {
                m_callbacks.mouseMove(m_event.motion.x, m_event.motion.y);
            }
            break;
        }

        case SDL_EVENT_MOUSE_WHEEL: {
            if (m_callbacks.mouseScroll) {
                m_callbacks.mouseScroll(m_event.wheel.y);
            }
            break;
        }

        case SDL_EVENT_WINDOW_RESIZED: {
            if (m_callbacks.resize) {
                u32 width = static_cast<u32>(m_event.window.data1);
                u32 height = static_cast<u32>(m_event.window.data2);
                m_callbacks.resize(width, height);
            }
            break;
        }

        case SDL_EVENT_WINDOW_FOCUS_LOST: {
            if (m_callbacks.lostFocus) {
                m_callbacks.lostFocus();
            }
            break;
        }
        }

    }
    return true;
}


auto Window::setKeyCallback(Window::KeyCallback key) -> void {
    m_callbacks.key = key;
}

auto Window::setMouseButtonCallback(Window::MouseButtonCallback button) -> void {
    m_callbacks.mouseButton = button;
}

auto Window::setMouseMoveCallback(Window::MouseMoveCallback move) -> void {
    m_callbacks.mouseMove = move;
}

auto Window::setMouseScrollCallback(Window::MouseScrollCallback scroll) -> void {
    m_callbacks.mouseScroll = scroll;
}

auto Window::setResizeCallback(Window::ResizeCallback resize) -> void {
    m_callbacks.resize = resize;
}

auto Window::setLostFocusCallback(Window::LostFocusCallback lostFocus) -> void {
    m_callbacks.lostFocus = lostFocus;
}

SDL_Window* Window::getNativeWindow() {
    return m_nativeWindow;
}

Window::~Window() {
    if (m_nativeWindow) {
        SDL_DestroyWindow(m_nativeWindow);
    }
    SDL_Quit();
}

MI_CORE_END