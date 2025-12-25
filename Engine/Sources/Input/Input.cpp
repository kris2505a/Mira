#include <PreCompHeader.hpp>
#include "Input.hpp"
#include "./Win32/Keyboard.hpp"
#include "./Win32/Mouse.hpp"
#include "Logger/Log.hpp"

namespace Mira {

bool Input::keyDown(Key key) {
	return Keyboard::m_keys[static_cast <uint32_t>(key)];
}

bool Input::keyUp(Key key) {
	return !Keyboard::m_keys[static_cast <uint32_t>(key)];
}

bool Input::buttonDown(Button button) {
	switch (button) {
	case Button::MouseLeft:
		return Mouse::m_left;

	case Button::MouseRight:
		return Mouse::m_right;

	case Button::MouseMiddle:
		return Mouse::m_middle;
	}
	return false;
}

bool Input::buttonUp(Button button) {
	switch (button) {
	case Button::MouseLeft:
		return !Mouse::m_left;

	case Button::MouseRight:
		return !Mouse::m_right;

	case Button::MouseMiddle:
		return !Mouse::m_middle;
	}
	return false;
}

int Input::getMouseX() {
	return Mouse::m_xPos;
}

int Input::getMouseY() {
	return Mouse::m_yPos;
}

}