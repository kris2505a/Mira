#pragma once
#include <string>
#include <array>

namespace Mira {

enum EventType {
	KeyPressed,
	KeyReleased,
	MouseButtonPressed,
	MouseButtonRelease,
	MouseMoved,
	MouseScrolled,
	WindowLostFocus,
	WindowClosed,
	WindowResized
};

constexpr std::array<std::string_view, 9> g_eventNames = {
    "Key Pressed",
    "Key Released",
    "Mouse Button Pressed",
    "Mouse Button Released",
    "Mouse Moved",
    "Mouse Scrolled",
    "Window Lost Focus",
    "Window Closed",
    "Window Resized"
};

class Event {
public:
	Event(EventType type) {
		m_type = type;
	}

	const EventType& getEventType() const {
		return m_type;
	}

	constexpr std::string_view getEventName() const {
		return g_eventNames[static_cast <size_t>(m_type)];
	}

private:
	EventType m_type;
};

}