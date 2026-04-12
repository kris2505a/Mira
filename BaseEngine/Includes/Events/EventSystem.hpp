#pragma once
#include <queue>
#include "Event.hpp"

namespace Mira {

class EventSystem {
public:
	void pushEvent(Event e) {
		m_events.push(e);
	}

	Event getEvent() {
		auto e = m_events.front();
		m_events.pop();
		return e;
	}

	bool isQueueEmpty() const {
		return m_events.empty();
	}

private:
	std::queue <Event> m_events;
};

}