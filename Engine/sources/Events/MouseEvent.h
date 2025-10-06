#pragma once
#include "Event.h"

namespace Mira {

class MouseButtonEvent : public Event {
protected:
	MouseButtonEvent(int button) : m_button(button) {}
	int m_button;
};

class MouseButtonPressEvent : public MouseButtonEvent {
public:
	MouseButtonPressEvent(int button) : MouseButtonEvent(button) {}
	std::string name() const override {
		return "MouseButtonPressed";
	}

	static std::string staticName() {
		return "MouseButtonPressed";
	}

	std::string print() override {
		return name() + ": " + std::to_string(m_button);
	}
};

class MouseButtonReleaseEvent : public MouseButtonEvent {
public:
	MouseButtonReleaseEvent(int button) : MouseButtonEvent(button) {}
	std::string name() const override {
		return "MouseButtonReleased";
	}

	static std::string staticName() {
		return "MouseButtonReleased";
	}

	std::string print() override {
		return name() + ": " + std::to_string(m_button);
	}
};

class MouseMoveEvent : public Event {
public:
	MouseMoveEvent(float x, float y) : m_xPos(x), m_yPos(y) {}
	std::string name() const override {
		return "MouseMoveEvent";
	}

	static std::string staticName() {
		return "MouseMoveEvent";
	}

	std::string print() override {
		return name() + ": (" + std::to_string(m_xPos) + ", " + std::to_string(m_yPos) +")";
	}

private:
	float m_xPos, m_yPos;
};

class MouseScrollEvent : public Event {
public:
	MouseScrollEvent(float x, float y) : m_xOffset(x), m_yOffset(y) {}
	std::string name() const override {
		return "MouseScrollEvent";
	}

	static std::string staticName() {
		return "MouseScrollEvent";
	}

	std::string print() override {
		return name() + ": (" + std::to_string(m_xOffset) + ", " + std::to_string(m_yOffset);
	}
private:
	float m_xOffset, m_yOffset;
};

}