#pragma once
#include "Window.hpp"
#include <SDL3/SDL.h>

namespace Mira {

class SDLWindow : public Window {
public:
    SDLWindow(unsigned int width, unsigned int height, const std::string& title);
    ~SDLWindow();
    void pollEvents()   override;
    mr::WindowHandle getHandle()    override;

private:
    SDL_Window* m_window = nullptr;
};

}
