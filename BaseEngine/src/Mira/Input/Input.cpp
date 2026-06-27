#include "MiraPch.hpp"
#include "Input.hpp"

namespace Mira {

Input Input::s_inputState;

auto Input::get() -> Input& {
    return s_inputState;
}

//KEY STATE
auto Input::setKeyState(Key key, State state) -> void {
    auto keyInd = static_cast<size_t>(key);
    get().keyState.set(keyInd, state == State::Down);
}

auto Input::isKeyDown(Key key) -> bool {
    auto keyInd = static_cast<size_t>(key);
    return get().keyState[keyInd] && !get().previousKeyState[keyInd];
}

auto Input::isKeyUp(Key key) -> bool {
    auto keyInd = static_cast<size_t>(key);
    return !get().keyState[keyInd] && get().previousKeyState[keyInd];
}

auto Input::isKeyHeld(Key key) -> bool {
    auto keyInd = static_cast<size_t>(key);
    return isKeyDown(key) || (get().keyState[keyInd] && get().previousKeyState[keyInd]);
}


//BUTTON STATE
auto Input::setButtonState(Button button, State state) -> void {
    auto buttonInd = static_cast<size_t>(button);
    get().buttonState.set(buttonInd, state == State::Down);
}

auto Input::isButtonDown(Button button) -> bool {
    auto buttonInd = static_cast<size_t>(button);
    return get().buttonState[buttonInd] && !get().previousButtonState[buttonInd];
}

auto Input::isButtonUp(Button button) -> bool {
    auto buttonInd = static_cast<size_t>(button);
    return !get().buttonState[buttonInd] && get().previousButtonState[buttonInd];
}

auto Input::isButtonHeld(Button button) -> bool {
    auto buttonInd = static_cast<size_t>(button);
    return get().buttonState[buttonInd] && get().previousButtonState[buttonInd];
}


//MOUSE ACTIONS
auto Input::mouseMove(Vec2 pos) -> void {

    if (get().firstMove) {
        get().firstMove = false;
        get().mousePosition = pos;
        return;
    }

    get().mouseDelta = pos - get().mousePosition;

    get().mousePosition = pos;
}

auto Input::mouseScroll(float offset) -> void {
    get().wheelOffset += offset;
}

auto Input::getMousePosition() -> Vec2 {
    return get().mousePosition;
}

auto Input::getMouseDelta() -> Vec2 {
    return get().mouseDelta;
}

auto Input::getMouseWheelOffset() -> float {
    return get().wheelOffset;
}

auto Input::lockMouse(bool cond) -> void {
    get().mouseLock = cond;
}

auto Input::endState() -> void {
    get().previousKeyState = get().keyState;
    get().previousButtonState = get().buttonState;

    get().mouseDelta = { 0.0f, 0.0f };

    get().wheelOffset = 0.0f;
}

auto Input::resetState() -> void {
    get().keyState.reset();
    get().previousKeyState.reset();

    get().buttonState.reset();
    get().previousButtonState.reset();

    get().mouseDelta = { 0.0f, 0.0f };


    get().wheelOffset = 0.0f;
}

}
