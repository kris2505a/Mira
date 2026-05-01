#include <Input/InputState.hpp>


namespace Mira {
std::array<bool, 256> InputState::s_currentState    = {};
std::array<bool, 256> InputState::s_previousState   = {};
std::array<bool, 256> InputState::s_repeatState     = {};
std::array<bool, 5>   InputState::s_mouseState      = {};

glm::vec2 InputState::s_mousePosition           = { 0.0f, 0.0f };
glm::vec2 InputState::s_previousMousePosition   = { 0.0f, 0.0f };
glm::vec2 InputState::s_mouseDelta              = { 0.0f, 0.0f };
glm::vec2 InputState::s_mouseWheel              = { 0.0f, 0.0f };
bool InputState::s_firstMouseMove               = true;

void InputState::beginFrame() {
    s_previousState = s_currentState;
    s_repeatState.fill(false);
    s_mouseDelta = { 0.0f, 0.0f };
    s_mouseWheel = { 0.0f, 0.0f };
}

void InputState::keyDown(int key, bool repeated) {
    if (key >= 256) {
        return;
    }

    s_currentState[key] = true;

    if (repeated) {
        s_repeatState[key] = true;
    }
}

void InputState::keyUp(int key) {
    if (key >= 256) {
        return;
    }

    s_currentState[key] = false;
 
}

void InputState::mouseButtonDown(int button) {
    s_mouseState[button] = true;
}

void InputState::mouseButtonUp(int button) {
    s_mouseState[button] = false;
}

void InputState::mouseMove(float x, float y) {
    if (s_firstMouseMove) {
        s_previousMousePosition = { x, y};
        s_mousePosition = { x, y };
        s_firstMouseMove = false;
        return;
    }

    s_mousePosition = { x, y };

    s_mouseDelta += s_mousePosition - s_previousMousePosition;
    s_previousMousePosition = s_mousePosition;
}

void InputState::mouseScroll(float xOffset, float yOffset) {
    s_mouseWheel.x += xOffset;
    s_mouseWheel.y += yOffset;
}

Key InputState::SDLScanToKey(int sc) {
    switch (sc)
    {
        // Letters
        case 4:  return Key::A;
        case 5:  return Key::B;
        case 6:  return Key::C;
        case 7:  return Key::D;
        case 8:  return Key::E;
        case 9:  return Key::F;
        case 10: return Key::G;
        case 11: return Key::H;
        case 12: return Key::I;
        case 13: return Key::J;
        case 14: return Key::K;
        case 15: return Key::L;
        case 16: return Key::M;
        case 17: return Key::N;
        case 18: return Key::O;
        case 19: return Key::P;
        case 20: return Key::Q;
        case 21: return Key::R;
        case 22: return Key::S;
        case 23: return Key::T;
        case 24: return Key::U;
        case 25: return Key::V;
        case 26: return Key::W;
        case 27: return Key::X;
        case 28: return Key::Y;
        case 29: return Key::Z;

        // Numbers
        case 30: return Key::D1;
        case 31: return Key::D2;
        case 32: return Key::D3;
        case 33: return Key::D4;
        case 34: return Key::D5;
        case 35: return Key::D6;
        case 36: return Key::D7;
        case 37: return Key::D8;
        case 38: return Key::D9;
        case 39: return Key::D0;

        // Control
        case 41: return Key::Escape;
        case 43: return Key::Tab;
        case 40: return Key::Enter;
        case 42: return Key::Backspace;
        case 44: return Key::Space;

        // Arrows
        case 82: return Key::Up;
        case 81: return Key::Down;
        case 80: return Key::Left;
        case 79: return Key::Right;

        // Modifiers
        case 225: return Key::LShift;
        case 229: return Key::RShift;
        case 224: return Key::LCtrl;
        case 228: return Key::RCtrl;
        case 226: return Key::LAlt;
        case 230: return Key::RAlt;

        default: return Key::Unknown;
    }
}

}
