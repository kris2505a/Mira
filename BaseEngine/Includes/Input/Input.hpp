#pragma once
#include <Core/Core.hpp>
#include "ScanCodes.hpp"
#include <vec2.hpp>

namespace Mira {

class MIRA_API Input {
public:
    static bool isKeyDown(Key key);
    static bool isKeyUp(Key key);
    static bool isButtonDown(Button button);
    static bool isButtonUp(Button button);
    static glm::vec2 getMousePosition();
    static glm::vec2 getMouseDelta();
    static glm::vec2 getMouseWheelDelta();
};

}
