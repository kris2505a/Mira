#pragma once
#include "Event.h"
#include <format>

namespace Mira {

class MIRA_API MouseMovedEvent : public Event {
private:
	float m_xPos, m_yPos;

public:
	MouseMovedEvent(float _x, float _y) : m_xPos(_x), m_yPos(_y) {}
	
	inline float getX() const { return m_xPos; }
	inline float getY() const { return m_yPos; }

	std::string toString() const override {
		return std::format("Mouse Moved: {}, {}", m_xPos, m_yPos);
	}

	EVENT_CLASS_TYPE(mouseMoved)
	EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)
};

class MIRA_API MouseScrolled : public Event {
private:
	float m_xOffset, m_yOffset;

public:
	MouseScrolled(float _x, float _y) : m_xOffset(_x), m_yOffset(_y) {}

	inline float getXOffset() const { return m_xOffset; }
	inline float getYOffset() const { return m_yOffset; }

	std::string toString() const override {
		return std::format("Mouse Scrolled: {}, {}", m_xOffset, m_yOffset);
	}

	EVENT_CLASS_TYPE(mouseScrolled)
	EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)
};

class MIRA_API MouseButtonEvent : public Event {
protected:
	int m_button;
	MouseButtonEvent(int _button) : m_button(_button) {}

public:
	inline int getMouseButton() const { return m_button; }
	EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)
};

class MIRA_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
	MouseButtonPressedEvent(int _button) : MouseButtonEvent(_button) {}
	std::string toString() const override {
		return std::format("Mouse Pressed: {}", m_button);
	}

	EVENT_CLASS_TYPE(mouseButtonPressed)
};

class MIRA_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
	MouseButtonReleasedEvent(int _button) : MouseButtonEvent(_button) {}
	std::string toString() const override {
		return std::format("Mouse Released: {}", m_button);
	}
	
	EVENT_CLASS_TYPE(mouseButtonReleased)
};

}