#pragma once

#include "Event.hpp"
#include <sstream>


namespace Cyan {

	class CYANAPI MouseMovedEvent : public Event {

	private:
		float m_Xpos, m_Ypos;

	public:
		MouseMovedEvent(float x, float y) : m_Xpos(x), m_Ypos(y) {}

		inline float getX() { return m_Xpos; }
		inline float getY() { return m_Ypos; }

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << m_Xpos << ", " << m_Ypos << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseMoved)
		EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)
	};

	class CYANAPI MouseScrolledEvent : public Event {
		
	private:
		float m_Xoffset, m_Yoffset;

	public:
		MouseScrolledEvent(float xOff, float yOff) : m_Xoffset(xOff), m_Yoffset(yOff) {}

		inline float getXoffset() { return m_Xoffset; }
		inline float getYoffset() { return m_Yoffset; }

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: (" << m_Xoffset << ", " << m_Yoffset << ")";
			return ss.str();
		}
		EVENT_CLASS_TYPE(mouseScrolled)
		EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)

	};

	class CYANAPI MouseButtonEvent : public Event {

	protected:
		int m_button;

	public:
		MouseButtonEvent(int button) : m_button(button) {}

		inline int getMouseButton() { return m_button; }
		EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)


	};

	class CYANAPI MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(mouseButtonPressed)
	};

	class CYANAPI MouseButtonReleasedEvent : public MouseButtonEvent{

	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(mouseButtonReleased)
	};
}