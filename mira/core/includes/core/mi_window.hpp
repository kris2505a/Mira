#pragma once
#include <SDL3/SDL.h>
#include "mi_core_api.hpp"
#include "mi_types.hpp"

#include <expected>


MI_CORE

class MI_CORE_API Window {
public:
    Window() = default;
    ~Window();
    auto pollEvents() -> bool;
    
public:
    static auto create() -> std::expected<Scope<Window>, std::string>;

private:
    SDL_Window* m_nativeWindow;
    std::string m_WindowTitle { "Mira" };
    u32 m_width{ 1280u };
    u32 m_height{ 720u };
    SDL_Event m_event;
};


MI_CORE_END