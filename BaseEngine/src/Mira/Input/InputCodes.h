#pragma once

namespace Mira {

enum class Button {
    Left,
    Right,
    Middle,
    X1,
    X2
};

enum class Key {

    // Letters
    A = 0x41,
    B, C, D, E, F,
    G, H, I, J, K,
    L, M, N, O, P,
    Q, R, S, T, U,
    V, W, X, Y, Z,

    // Numbers
    Num0 = 0x30,
    Num1, Num2, Num3,
    Num4, Num5, Num6,
    Num7, Num8, Num9,

    // Function Keys
    F1 = 0x70,
    F2, F3, F4,
    F5, F6, F7,
    F8, F9, F10,
    F11, F12,

    // Control Keys
    Space      = 0x20,
    Enter      = 0x0D,
    Escape     = 0x1B,
    Backspace  = 0x08,
    Tab        = 0x09,

    LeftShift  = 0xA0,
    RightShift = 0xA1,

    LeftCtrl   = 0xA2,
    RightCtrl  = 0xA3,

    LeftAlt    = 0xA4,
    RightAlt   = 0xA5,

    // Arrow Keys
    Left  = 0x25,
    Up    = 0x26,
    Right = 0x27,
    Down  = 0x28,

    // Mouse Buttons
    MouseLeft   = 0x01,
    MouseRight  = 0x02,
    MouseMiddle = 0x04
};

}
