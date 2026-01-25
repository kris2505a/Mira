#include "Input.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

bool Input::isKeyDown(Key key) {
    return Keyboard::m_keys[static_cast <size_t>(key)];
}

bool Input::isKeyUp(Key key){
    return !Keyboard::m_keys[static_cast <size_t>(key)];
}

bool Input::isButtonDown(Button button) {
    switch (button) {
    case Button::Left:
        return Mouse::m_left;

    case Button::Right:
        return Mouse::m_right;

    case Button::Middle:
        return Mouse::m_middle;

    case Button::X1:
        return Mouse::m_x1;

    case Button::X2:
        return Mouse::m_x2;
    }

    return false;
}

bool Input::isButtonUp(Button button) {
    switch (button) {
    case Button::Left:
        return !Mouse::m_left;

    case Button::Right:
        return !Mouse::m_right;

    case Button::Middle:
        return !Mouse::m_middle;

    case Button::X1:
        return !Mouse::m_x1;

    case Button::X2:
        return !Mouse::m_x2;
    }

    return false;
}
