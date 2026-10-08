#pragma once
#include <SDL3/SDL.h>
#include "mi_core_api.hpp"
#include "mi_types.hpp"

#include <expected>
#include <functional>

MI_CORE

class MI_CORE_API Window {

    using KeyCallback = std::function<void(u32, bool, bool)>; //key, repeat, down = true, up = false
    using MouseButtonCallback = std::function<void(u32, bool)>; //key, down = true, up = false
    using MouseMoveCallback = std::function<void(f32, f32)>;
    using MouseScrollCallback = std::function<void(f32)>;
    using ResizeCallback = std::function<void(u32, u32)>;
    using LostFocusCallback = std::function<void()>;
    
    struct _Callbacks {
        KeyCallback key;
        MouseButtonCallback mouseButton;
        MouseMoveCallback mouseMove;
        MouseScrollCallback mouseScroll;
        ResizeCallback resize;
        LostFocusCallback lostFocus;
    };

public:
    Window() = default;
    ~Window();
    auto pollEvents() -> bool;
    auto setKeyCallback(KeyCallback key) -> void;
    auto setMouseButtonCallback(MouseButtonCallback button) -> void;
    auto setMouseMoveCallback(MouseMoveCallback move) -> void;
    auto setMouseScrollCallback(MouseScrollCallback scroll) -> void;
    auto setResizeCallback(ResizeCallback resize) -> void;
    auto setLostFocusCallback(LostFocusCallback lostFocus) -> void;

    SDL_Window* getNativeWindow();
    
public:
    static auto create() -> std::expected<Scope<Window>, std::string>;

private:
    _Callbacks m_callbacks;
    SDL_Window* m_nativeWindow;
    std::string m_WindowTitle { "Mira" };
    u32 m_width{ 1280u };
    u32 m_height{ 720u };
    SDL_Event m_event;
};


MI_CORE_END