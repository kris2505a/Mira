#include "MiraPch.h"
#include "Input.h"

namespace Mira {

Input Input::s_inputState;

Input& Input::get() {
    return s_inputState;
}

//KEY STATE
void Input::setKeyState(Key key, State state) {
    auto keyInd = static_cast<size_t>(key);
    get().keyState.set(keyInd, state == State::Down);
}

bool Input::isKeyDown(Key key) {
    auto keyInd = static_cast<size_t>(key);
    return get().keyState[keyInd] && !get().previousKeyState[keyInd];
}

bool Input::isKeyUp(Key key) {
    auto keyInd = static_cast<size_t>(key);
    return !get().keyState[keyInd] && get().previousKeyState[keyInd];
}

bool Input::isKeyHeld(Key key) {
    auto keyInd = static_cast<size_t>(key);
    return get().keyState[keyInd] && get().previousKeyState[keyInd];
}


//BUTTON STATE
void Input::setButtonState(Button button, State state) {
    auto buttonInd = static_cast<size_t>(button);
    get().buttonState.set(buttonInd, state == State::Down);
}

bool Input::isButtonDown(Button button) {
    auto buttonInd = static_cast<size_t>(button);
    return get().buttonState[buttonInd] && !get().previousButtonState[buttonInd];
}

bool Input::isButtonUp(Button button) {
    auto buttonInd = static_cast<size_t>(button);
    return !get().buttonState[buttonInd] && get().previousButtonState[buttonInd];
}

bool Input::isButtonHeld(Button button) {
    auto buttonInd = static_cast<size_t>(button);
    return get().buttonState[buttonInd] && get().previousButtonState[buttonInd];
}


//MOUSE ACTIONS
void Input::mouseMove(Vec2D pos) {

    if (get().firstMove) {
        get().firstMove = false;
        get().mousePosition = pos;
        return;
    }

    get().mouseDelta = pos - get().mousePosition;

    get().mousePosition = pos;
}

void Input::mouseScroll(float offset) {
    get().wheelOffset += offset;
}

Vec2D Input::getMousePosition() {
    return get().mousePosition;
}

Vec2D Input::getMouseDelta() {
    return get().mouseDelta;
}

float Input::getMouseWheelOffset() {
    return get().wheelOffset;
}

void Input::endState() {
    get().previousKeyState = get().keyState;
    get().previousButtonState = get().buttonState;

    get().mouseDelta = { 0.0f, 0.0f };

    get().wheelOffset = 0.0f;
}

void Input::resetState() {
    get().keyState.reset();
    get().previousKeyState.reset();

    get().buttonState.reset();
    get().previousButtonState.reset();

    get().mouseDelta = { 0.0f, 0.0f };


    get().wheelOffset = 0.0f;
}

}
