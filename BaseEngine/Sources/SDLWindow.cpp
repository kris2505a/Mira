#include <Window/SDLWindow.hpp>
#include <Logging/Log.hpp>

namespace Mira {

SDLWindow::SDLWindow(unsigned int width, unsigned int height, const std::string& title) 
        : Window(width, height, title){

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        Logger::Log(LogType::Error, "Unable to init SDL!");
        std::exit(-1);
    }

    m_window = SDL_CreateWindow(
        m_title.c_str(),
        static_cast<int>(m_width),
        static_cast<int>(m_height),
        SDL_WINDOW_RESIZABLE
    );
    Logger::Log(LogType::Info, "Window Created! {}x{}", m_width, m_height);
    Logger::Log(LogType::Info, "Window Handler: SDL3 - Version: {}", SDL_MAJOR_VERSION);
}

void SDLWindow::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
        {
            WindowClosedEvent e;
            callback(e);
            break;
        }

        case SDL_EVENT_WINDOW_RESIZED:
        {
            int w, h;
            SDL_GetWindowSize(m_window, &w, &h);
            m_width = static_cast<unsigned int>(w);
            m_height = static_cast<unsigned int>(h);
            WindowResizedEvent e(w, h);
            callback(e);
            break;
        }

        case SDL_EVENT_KEY_DOWN:
        {
            bool repeated = false;
            if(event.key.repeat) {
                repeated = true;
            }

            KeyPressedEvent e(event.key.key, repeated);
            callback(e);
            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            KeyReleasedEvent e(event.key.key);
            callback(e);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            MouseButtonPressedEvent e(event.button.button);
            callback(e);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            MouseButtonReleasedEvent e(event.key.key);
            callback(e);
            break;
        }

        case SDL_EVENT_MOUSE_MOTION:
        {
            MouseMovedEvent e(event.motion.x, event.motion.y);
            callback(e);
            break;
        }

        case SDL_EVENT_MOUSE_WHEEL:
        {
            MouseScrolledEvent e(event.wheel.x, event.wheel.y);
        }

        }
    }
}

HWND SDLWindow::getHandle() {
    void* handle = SDL_GetPointerProperty(
                SDL_GetWindowProperties(m_window),
                SDL_PROP_WINDOW_WIN32_HWND_POINTER,
                NULL
    );

    return (HWND) handle;
}

SDLWindow::~SDLWindow() {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


}
