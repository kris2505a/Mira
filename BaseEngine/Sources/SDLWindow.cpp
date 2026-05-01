#include <Window/SDLWindow.hpp>
#include <Logging/Log.hpp>
#include <Input/InputState.hpp>

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
    InputState::beginFrame();
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

            auto key = InputState::SDLScanToKey(event.key.scancode);

            InputState::keyDown(key, repeated);

            KeyPressedEvent e(key, repeated);
            callback(e);
            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            auto key = InputState::SDLScanToKey(event.key.scancode);
            InputState::keyUp(key);
            KeyReleasedEvent e(key);
            callback(e);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            InputState::mouseButtonDown(event.button.button);
            MouseButtonPressedEvent e(event.button.button);
            callback(e);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            InputState::mouseButtonUp(event.button.button);
                MouseButtonReleasedEvent e(event.button.button);
            callback(e);
            break;
        }

        case SDL_EVENT_MOUSE_MOTION:
        {
            InputState::mouseMove(event.motion.x, event.motion.y);
            MouseMovedEvent e(event.motion.x, event.motion.y);
            callback(e);
            break;
        }

        case SDL_EVENT_MOUSE_WHEEL:
        {
            InputState::mouseScroll(event.wheel.x, event.wheel.y);
            MouseScrolledEvent e(event.wheel.x, event.wheel.y);
        }

        }
    }
}

mr::WindowHandle SDLWindow::getHandle() {
    mr::WindowHandle handle;
#ifdef PLATFORM_WINDOWS
    void* winHandle = SDL_GetPointerProperty(
        SDL_GetWindowProperties(m_window),
        SDL_PROP_WINDOW_WIN32_HWND_POINTER,
        NULL
    );
    handle.hwnd = (HWND) winHandle;
#endif

    return handle;
}

SDLWindow::~SDLWindow() {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


}
