#pragma once
#include <string>

#include "helpers/mi_types.hpp"
#include "helpers/mi_win_hpr.hpp"
#include "mi_core_api.hpp"

#include <functional>

namespace mira::core {

class MI_CORE_API Window {
    //Callback functions
    struct _Win32 {
        HWND window{ nullptr };
        HINSTANCE instance{ nullptr };
        MSG message{};
    };
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
    Window();
    ~Window();
    auto pollEvents() -> bool;
    auto getWin32Handle() const -> HWND;
    auto setKeyCallback(KeyCallback key) -> void;
    auto setMouseButtonCallback(MouseButtonCallback button) -> void;
    auto setMouseMoveCallback(MouseMoveCallback move) -> void;
    auto setMouseScrollCallback(MouseScrollCallback scroll) -> void;
    auto setResizeCallback(ResizeCallback resize) -> void;
    auto setLostFocusCallback(LostFocusCallback lostFocus) -> void;

private:
    static LRESULT windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    _Callbacks mCallbacks;


private:
    _Win32 mWindowHandles;
    std::string mclassName{ "MiraWindow" };
    std::string mWindowName{ "Mira" };
    u32 mWidth{ 1280 };
    u32 mHeight{ 720 };
};


}
