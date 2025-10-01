#pragma once
#include <string>
#include <Base/MiraAPI.h>

namespace Mira {

class MIRA_API Event {
	friend class EventDispatcher;
public:
	Event() = default;
	~Event() = default;
	virtual std::string name() const = 0;
	static std::string staticName() { return "None"; }
	virtual std::string print() = 0;

private:
	bool m_handled = false;
};

class MIRA_API EventDispatcher {
public:	
	EventDispatcher(Event& event) : r_event(event) {}
	template <typename T, typename F>
	bool dispatch(const F& func) {
		if (r_event.name() == T::staticName()) {
			r_event.m_handled = func(static_cast<T&>(r_event));
			return true;
		}
		return false;
	}

private:
	Event& r_event;
};

}