#pragma once
#include "Event.hpp"
#include <functional>

namespace Mira {

class Dispatcher {
    template<typename T>
    using EventFn = std::function<bool(T&)>;

public:
    Dispatcher(Event& event)
            :m_event(event){}

    template<typename T>
    bool dispatch(EventFn<T> func) {
        if(m_event.getEventType() == T::getStaticType() && !m_event.Handled) {
            m_event.Handled = func(*(T*)&m_event);
            return true;
        }
        return false;
    }

private:
    Event& m_event;
};

}
