#pragma once
#include "Signal.hpp"

namespace Mira {

class MouseButtonSignal : public Signal {
public:
	Button getButton() const {
		return m_button;
	}

protected:
	MouseButtonSignal(Button button) : m_button(button) {}
	~MouseButtonSignal() = default;
	SignalType type() const {
		return SignalType::NONE;
	}
	std::string name() const {
		return "None";
	}
	Button m_button;
};

class MouseButtonDownSignal : public MouseButtonSignal {
public:
	MouseButtonDownSignal(Button button) : MouseButtonSignal(button) {}
	~MouseButtonDownSignal() = default;
	SignalType type() const {
		return SignalType::ButtonDown;
	}
	std::string name() const {
		return "ButtonDown";
	}
};

class MouseButtonUpSignal : public MouseButtonSignal {
public:
	MouseButtonUpSignal(Button button) : MouseButtonSignal(button) {}
	~MouseButtonUpSignal() = default;
	SignalType type() const {
		return SignalType::ButtonUp;
	}
	std::string name() const {
		return "ButtonUp";
	}
};

class MouseMoveSignal : public Signal {
public:
	MouseMoveSignal(int x, int y) : m_xPos(x), m_yPos(y) {}
	~MouseMoveSignal() = default;
	int getX() const { return m_xPos; }
	int getY() const { return m_yPos; }

	SignalType type() const {
		return SignalType::MouseMove;
	}
	std::string name() const {
		return "MouseMove";
	}

private:
	int m_xPos, m_yPos;
};

class MouseScrollSignal : public Signal {
public:
	MouseScrollSignal(int x, int y) : m_xOffset(x), m_yOffset(y) {}
	~MouseScrollSignal() = default;
	int getX() const { return m_xOffset; }
	int getY() const { return m_yOffset; }
	
	SignalType type() const {
		return SignalType::MouseScroll;
	}
	std::string name() const {
		return "MouseScroll";
	}

private:
	int m_xOffset, m_yOffset;
};

}