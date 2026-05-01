#pragma once
#include <array>
#include <vec2.hpp>
#include "ScanCodes.hpp"

namespace Mira {

class InputState {
    friend class Input;
public:
    static void beginFrame();
    static void keyUp(int key);
    static void keyDown(int key, bool repeated);
    static void mouseButtonDown(int key);
    static void mouseButtonUp(int key);
    static void mouseMove(float x, float y);
    static void mouseScroll(float xOffset, float yOffset);

    static Key SDLScanToKey(int sc);

private:
    static std::array <bool, 256> s_currentState;
    static std::array <bool, 256> s_previousState;
    static std::array <bool, 256> s_repeatState;

    static std::array <bool, 5>   s_mouseState;

    static glm::vec2 s_mousePosition;
    static glm::vec2 s_previousMousePosition;
    static glm::vec2 s_mouseDelta;

    static bool s_firstMouseMove;

    static glm::vec2 s_mouseWheel;

};

}
