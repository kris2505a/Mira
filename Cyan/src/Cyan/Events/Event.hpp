#pragma once
#include "Cyan/core.hpp"




namespace Cyan {
	
	enum class eventType {

		None = 0,
		windowClose, windowResize, windowFocus, windowLostFocus, windowMoved,
		appTick, appUpdate, appRender,
		keyPressed, keyReleased,
		mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScrolled

	};

	enum eventCategory {
		None = 0,
		eventCategoryApplication = BIT(0),
		eventCategoryInput = BIT(1),
		eventCategoryKeyboard = BIT(2),
		eventCategoryMouse = BIT(3),
		eventCategoryMouseButton = BIT(4)
	};

	class CYANAPI Event {

		friend class EventDispatcher;
	
	protected:
		bool m_handled{ false };

	public:
		virtual eventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(eventCategory category) { return getCategoryFlags() & category; }
	};


	class EventDispatcher {

		template <typename T>
		using EventFn = std::function<bool(T&)>;

	private:
		Event& m_event;

	public:
		EventDispatcher(Event& event) : m_event(event) {}

		template <typename T>
		bool dispatch(EventFn<T> func) {
			if (m_event.getEventType() == T::getStaticType()) {
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}

	};

	inline std::ostream& operator <<(std::ostream& ostr, const Event& event) {
		return ostr << event.toString();
	}

#define EVENT_CLASS_TYPE(tyPE) static eventType getStaticType() { return eventType::##tyPE; }\
								virtual eventType getEventType() const override { return getStaticType(); } \
								virtual const char* getName() const override { return #tyPE; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }
}