#pragma once
#include "Mira/Core/Core.hpp"
#include <string>

namespace Mira {


enum EventCategory {
    WindowEvent         = BIT(1),
    KeyboardEvent       = BIT(2),
    MouseEvent          = BIT(3),
    InputEvent          = BIT(4),
    SystemEvent         = BIT(5)
};

enum class EventType {

    None,

    //Keyboard Events
    KeyPressed,
    KeyReleased,

    //MouseEvents
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,

    //WindowEvents
    WindowClosed,
    WindowResized,
    WindowLostFocus
};

#define CREATE_BODY(type, category) \
    const char* getName() const override { return #type; } \
    EventType getType() const override { return type; } \
    int getCategoryFlags() const override { return category; } \
    static EventType getStaticType() { return type; }

class Event {
public:
    Event() = default;
    virtual ~Event() = default;
    [[nodiscard]]
    inline bool isInCategory(const EventCategory category) const {
        return getCategoryFlags() & static_cast<int>(category);
    }
    [[nodiscard]]
    virtual const char* getName() const = 0;
    [[nodiscard]]
    virtual EventType getType() const = 0;
    [[nodiscard]]
    virtual int getCategoryFlags() const = 0;
    [[nodiscard]]
    virtual inline std::string getEventInfoString() const = 0;

    bool handled = false;
};

class EventDispatcher {
public:
    EventDispatcher(Event& e) : m_event(e) {}

    template <typename T, typename F>
    bool dispatch(const F& eventFn) {
        if (m_event.getType() == T::getStaticType()) {
            m_event.handled = eventFn(static_cast<T&>(m_event));
            return true;
        }
        return false;
    }

private:
    Event& m_event;
};


}
