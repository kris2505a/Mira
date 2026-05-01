#include <Input/Input.hpp>
#include <Input/InputState.hpp>

namespace Mira {

bool Input::isKeyDown(Key key) {
    return InputState::s_currentState[key];
}

bool Input::isKeyUp(Key key) {
    return InputState::s_currentState[key];
}

bool Input::isButtonDown(Button button) {
    return InputState::s_mouseState[button];
}

bool Input::isButtonUp(Button button) {
    return InputState::s_mouseState[button];
}

glm::vec2 Input::getMousePosition() {
    return InputState::s_mousePosition;
}

glm::vec2 Input::getMouseDelta() {
    return InputState::s_mouseDelta;
}

glm::vec2 Input::getMouseWheelDelta() {
    return InputState::s_mouseWheel;
}

}