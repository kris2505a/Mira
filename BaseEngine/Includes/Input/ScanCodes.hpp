#pragma once
#include <cstdint>

namespace Mira {

enum Key : uint8_t
{
    // =========================
    // ASCII-like (0–127)
    // =========================
    Space = 32,

    D0 = 48, D1, D2, D3, D4,
    D5, D6, D7, D8, D9,

    A = 65, B, C, D, E,
    F, G, H, I, J,
    K, L, M, N, O,
    P, Q, R, S, T,
    U, V, W, X, Y, Z,

    // =========================
    // Special (128+)
    // =========================
    Escape = 128,
    Tab,
    Enter,
    Backspace,

    Insert,
    Delete,
    Home,
    End,
    PageUp,
    PageDown,

    Up,
    Down,
    Left,
    Right,

    // Function keys
    F1, F2, F3, F4,
    F5, F6, F7, F8,
    F9, F10, F11, F12,

    // Modifiers
    LShift,
    RShift,
    LCtrl,
    RCtrl,
    LAlt,
    RAlt,

    Unknown = 255
};

enum Button : uint8_t {
    LeftMouseButton = 0,
    MiddleMosueButton,
    RightMosueButton,
    XMouseButton1,
    XMouseButton2
};

}