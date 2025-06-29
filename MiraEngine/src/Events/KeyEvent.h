#pragma once
#include "Event.h"
#include <format>

namespace Mira {

class MIRA_API KeyEvent : public Event {

protected:
	int m_keyCode;
	KeyEvent(int _keyCode) : m_keyCode(_keyCode) {}

public:
	inline int getKeyCode() const { return m_keyCode; }
	EVENT_CLASS_CATEGORY(eventCategoryKeyboard | eventCategoryInput)
};

class MIRA_API KeyPressedEvent : public KeyEvent {
private:
	int m_repeatCount;

public:
	KeyPressedEvent(int _keyCode, int _repeatCount) : KeyEvent(_keyCode), m_repeatCount(_repeatCount) {}

	inline int getRepeatCount() const { return m_repeatCount; }
	std::string toString() const override {
		return std::format("Key Pressed: {} (Repeated: {})", m_keyCode, m_repeatCount);
	}

	EVENT_CLASS_TYPE(keyPressed)
};

class MIRA_API KeyReleasedEvent : public KeyEvent {

public:
	KeyReleasedEvent(int _keyCode) : KeyEvent(_keyCode) {}

	std::string toString() const override {
		return std::format("Key Released: {}", m_keyCode);
	}

	EVENT_CLASS_TYPE(keyReleased)
};

}