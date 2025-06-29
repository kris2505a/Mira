#pragma once

#include <Core/MiraCore.h>

#include <string>
#include <functional>

namespace Mira {

enum class EventType {
	none = 0,
	windowClose, windowResize, windowFocus, windowLostFocus, windowMoved,
	appTick, appUpdate,	appRender,
	keyPressed, keyReleased,
	mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScrolled
};

enum EventCategory {
	none = 0,
	eventCategoryApplication = BIT(0),
	eventCategoryInput = BIT(1),
	eventCategoryKeyboard = BIT(2),
	eventCategoryMouse = BIT(3),
	eventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; } \
							   virtual EventType getEventType() const override { return getStaticType(); } \
							   virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

class MIRA_API Event {

	friend class EventDispatcher;

protected:
	bool m_handled = false;

public:
	virtual EventType getEventType() const = 0;
	virtual	const char* getName() const = 0;
	virtual int getCategoryFlags() const = 0;
	virtual std::string toString() const { return getName(); }
	
	inline bool isInCategory(EventCategory category) {
		return getCategoryFlags() & category;
	}

	inline bool isHandled() const { return m_handled; }
};

class EventDispatcher {
	template<typename T>
	using eventFn = std::function<bool(T&)>;
private:
	Event& m_event;
	
public:
	EventDispatcher(Event& _event) : m_event(_event) {}

	template <typename T>
	bool dispatch(eventFn<T> func) {
		if (m_event.getEventType() == T::getStaticType()) {
			m_event.m_handled = func(*(T*)&m_event);
			return true;	
		}
		return false;
	}
};


}