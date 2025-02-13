#pragma once

#include "Event.hpp"
#include <sstream>


namespace Cyan {

	class CYANAPI WindowResizeEvent : public Event {

	private:
		unsigned int m_width, m_height;

	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

		inline unsigned int getWidth() { return m_width; }
		inline unsigned int getHeight() { return m_height; }

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: (" << m_width << ", " << m_height << ")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(eventCategoryApplication)
		EVENT_CLASS_TYPE(windowResize)
	};

	class CYANAPI windowCloseEvent : public Event {
	public:
		windowCloseEvent() = default;

		EVENT_CLASS_CATEGORY(eventCategoryApplication)
		EVENT_CLASS_TYPE(windowClose)
	};

	class CYANAPI AppTickEvent : public Event {
	public:
		AppTickEvent() = default;

		EVENT_CLASS_CATEGORY(eventCategoryApplication)
		EVENT_CLASS_TYPE(appTick)
	};

	class CYANAPI AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_CATEGORY(eventCategoryApplication)
		EVENT_CLASS_TYPE(appUpdate)
	};

	class CYANAPI AppRenderEvent : public Event {
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_CATEGORY(eventCategoryApplication)
		EVENT_CLASS_TYPE(appRender)
	};
}