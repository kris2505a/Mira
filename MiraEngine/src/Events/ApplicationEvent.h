#pragma once

#include "Event.h"
#include <format>

namespace Mira {

class MIRA_API WindowResizeEvent : public Event {
private:
	unsigned int m_width, m_height;

public:
	WindowResizeEvent(unsigned int _width, unsigned int _height)
		: m_width(_width), m_height(_height) { }
	
	inline unsigned int getWidth() const { return m_width; }
	inline unsigned int getHeight() const { return m_height; }

	std::string toString() const override {
		return std::format("Window Resize Event: {}, {}", m_width, m_height);
	}

	EVENT_CLASS_TYPE(windowResize)
	EVENT_CLASS_CATEGORY(eventCategoryApplication)
};

class MIRA_API WindowCloseEvent : public Event {
public:
	WindowCloseEvent() {}

	EVENT_CLASS_TYPE(windowClose)
	EVENT_CLASS_CATEGORY(eventCategoryApplication)
};

class MIRA_API AppTickEvent : public Event {
public:
	AppTickEvent() {}

	EVENT_CLASS_TYPE(appTick)
	EVENT_CLASS_CATEGORY(eventCategoryApplication)
};

class MIRA_API AppUpdateEvent : public Event {
public:
	AppUpdateEvent() {}

	EVENT_CLASS_TYPE(appUpdate)
	EVENT_CLASS_CATEGORY(eventCategoryApplication)
};

class MIRA_API AppRenderEvent : public Event {
public:
	AppRenderEvent() {}

	EVENT_CLASS_TYPE(appRender)
	EVENT_CLASS_CATEGORY(eventCategoryApplication)
};

}