#pragma once
#include <cstdint>
#include <Windows.h>

namespace Mira {

enum class Key : uint16_t
{
    None = 0x00,
    // --- Control keys ---
    Backspace = VK_BACK,      // 0x08
    Tab = VK_TAB,       // 0x09
    Enter = VK_RETURN,    // 0x0D
    Shift = VK_SHIFT,     // 0x10 (generic)
    Control = VK_CONTROL,   // 0x11 (generic)
    Alt = VK_MENU,      // 0x12 (generic)
    Pause = VK_PAUSE,     // 0x13
    CapsLock = VK_CAPITAL,   // 0x14
    Escape = VK_ESCAPE,    // 0x1B
    Space = VK_SPACE,     // 0x20
    PageUp = VK_PRIOR,     // 0x21
    PageDown = VK_NEXT,      // 0x22
    End = VK_END,       // 0x23
    Home = VK_HOME,      // 0x24

    Left = VK_LEFT,      // 0x25
    Up = VK_UP,        // 0x26
    Right = VK_RIGHT,     // 0x27
    Down = VK_DOWN,      // 0x28

    PrintScreen = VK_SNAPSHOT,  // 0x2C
    Insert = VK_INSERT,    // 0x2D
    Delete = VK_DELETE,    // 0x2E

    // --- 0-9 ---
    D0 = 0x30,
    D1 = 0x31,
    D2 = 0x32,
    D3 = 0x33,
    D4 = 0x34,
    D5 = 0x35,
    D6 = 0x36,
    D7 = 0x37,
    D8 = 0x38,
    D9 = 0x39,

    // --- A-Z ---
    A = 0x41,
    B = 0x42,
    C = 0x43,
    D = 0x44,
    E = 0x45,
    F = 0x46,
    G = 0x47,
    H = 0x48,
    I = 0x49,
    J = 0x4A,
    K = 0x4B,
    L = 0x4C,
    M = 0x4D,
    N = 0x4E,
    O = 0x4F,
    P = 0x50,
    Q = 0x51,
    R = 0x52,
    S = 0x53,
    T = 0x54,
    U = 0x55,
    V = 0x56,
    W = 0x57,
    X = 0x58,
    Y = 0x59,
    Z = 0x5A,

    // --- Windows / System ---
    LeftSuper = VK_LWIN,      // 0x5B
    RightSuper = VK_RWIN,      // 0x5C
    Menu = VK_APPS,      // 0x5D

    Sleep = VK_SLEEP,     // 0x5F

    // --- Numpad ---
    Num0 = VK_NUMPAD0,   // 0x60
    Num1 = VK_NUMPAD1,   // 0x61
    Num2 = VK_NUMPAD2,   // 0x62
    Num3 = VK_NUMPAD3,   // 0x63
    Num4 = VK_NUMPAD4,   // 0x64
    Num5 = VK_NUMPAD5,   // 0x65
    Num6 = VK_NUMPAD6,   // 0x66
    Num7 = VK_NUMPAD7,   // 0x67
    Num8 = VK_NUMPAD8,   // 0x68
    Num9 = VK_NUMPAD9,   // 0x69

    NumMultiply = VK_MULTIPLY,  // 0x6A
    NumAdd = VK_ADD,       // 0x6B
    NumSeparator = VK_SEPARATOR, // 0x6C (rare)
    NumSubtract = VK_SUBTRACT,  // 0x6D
    NumDecimal = VK_DECIMAL,   // 0x6E
    NumDivide = VK_DIVIDE,    // 0x6F

    // --- Function keys ---
    F1 = VK_F1,
    F2 = VK_F2,
    F3 = VK_F3,
    F4 = VK_F4,
    F5 = VK_F5,
    F6 = VK_F6,
    F7 = VK_F7,
    F8 = VK_F8,
    F9 = VK_F9,
    F10 = VK_F10,
    F11 = VK_F11,
    F12 = VK_F12,
    F13 = VK_F13,
    F14 = VK_F14,
    F15 = VK_F15,
    F16 = VK_F16,
    F17 = VK_F17,
    F18 = VK_F18,
    F19 = VK_F19,
    F20 = VK_F20,
    F21 = VK_F21,
    F22 = VK_F22,
    F23 = VK_F23,
    F24 = VK_F24,

    // --- Lock keys ---
    NumLock = VK_NUMLOCK,   // 0x90
    ScrollLock = VK_SCROLL,    // 0x91

    // --- Left / Right specific modifiers ---
    LeftShift = VK_LSHIFT,    // 0xA0
    RightShift = VK_RSHIFT,    // 0xA1
    LeftControl = VK_LCONTROL,  // 0xA2
    RightControl = VK_RCONTROL,  // 0xA3
    LeftAlt = VK_LMENU,     // 0xA4
    RightAlt = VK_RMENU,     // 0xA5

    // --- Browser / Media keys (optional but real VKs) ---
    BrowserBack = VK_BROWSER_BACK,
    BrowserForward = VK_BROWSER_FORWARD,
    BrowserRefresh = VK_BROWSER_REFRESH,
    BrowserStop = VK_BROWSER_STOP,
    BrowserSearch = VK_BROWSER_SEARCH,
    BrowserFavorites = VK_BROWSER_FAVORITES,
    BrowserHome = VK_BROWSER_HOME,

    VolumeMute = VK_VOLUME_MUTE,
    VolumeDown = VK_VOLUME_DOWN,
    VolumeUp = VK_VOLUME_UP,
    MediaNext = VK_MEDIA_NEXT_TRACK,
    MediaPrev = VK_MEDIA_PREV_TRACK,
    MediaStop = VK_MEDIA_STOP,
    MediaPlayPause = VK_MEDIA_PLAY_PAUSE,

    // --- OEM keys (layout-dependent) ---
    Semicolon = VK_OEM_1,     // ;:
    Plus = VK_OEM_PLUS,  // =+
    Comma = VK_OEM_COMMA, // ,<
    Minus = VK_OEM_MINUS, // -_
    Period = VK_OEM_PERIOD,// .>
    Slash = VK_OEM_2,     // /?
    GraveAccent = VK_OEM_3,     // `~
    LeftBracket = VK_OEM_4,     // [{
    Backslash = VK_OEM_5,     // \|
    RightBracket = VK_OEM_6,     // ]}
    Apostrophe = VK_OEM_7      // '"
};


enum class Button : uint8_t
{
    Left = VK_LBUTTON,
    Right = VK_RBUTTON,
    Middle = VK_MBUTTON,
    X1 = VK_XBUTTON1,
    X2 = VK_XBUTTON2
};

}