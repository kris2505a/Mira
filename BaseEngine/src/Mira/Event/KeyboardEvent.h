#pragma once
#include "Event.h"
#include <format>

namespace Mira {

class KeyboardEvent : public Event {

public:    
    [[nodiscard]]
    inline int getKey() const {
        return m_key;
    }
    
protected:
    KeyboardEvent(int key) : m_key(key) {}

private:
    int m_key;

};

class KeyPressEvent : public KeyboardEvent {
public:
    KeyPressEvent(int key, bool repeat) : KeyboardEvent(key), m_repeat(repeat) {}
    
    CREATE_BODY(EventType::KeyPressed, EventCategory::KeyboardEvent | EventCategory::InputEvent)
    
    [[nodiscard]]
    inline std::string getEventInfoString() const override {
        return std::format("KeyPressEvent: {} (Repeat = {})", getKey(), m_repeat);
    }
private:
    bool m_repeat;
};

class KeyReleaseEvent : public KeyboardEvent {
public:
    KeyReleaseEvent(int key) : KeyboardEvent(key) {}

    CREATE_BODY(EventType::KeyReleased, EventCategory::KeyboardEvent | EventCategory::InputEvent)

    [[nodiscard]]
    inline std::string getEventInfoString() const override {
        return std::format("KeyReleaseEvent: {}", getKey());
    }
};

}