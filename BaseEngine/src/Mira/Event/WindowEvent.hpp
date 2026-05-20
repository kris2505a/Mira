#pragma once
#include "Event.hpp"
#include <format>

namespace Mira {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

    CREATE_BODY(EventType::WindowResized, EventCategory::WindowEvent)
    [[nodiscard]]
    inline std::string getEventInfoString() const override {
        return std::format("WindowResized: {} x {}", m_width, m_height);
    }

    inline unsigned int getWidth() const {
        return m_width;
    }

    inline unsigned int getHeight() const {
        return m_height;
    }

private:
    unsigned int m_width;
    unsigned int m_height;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    CREATE_BODY(EventType::WindowClosed, EventCategory::WindowEvent | EventCategory::SystemEvent)

    [[nodiscard]]
    inline std::string getEventInfoString() const override {
         return "WindowClosed";
    }
};

class WindowLostFocusEvent : public Event {
public:
    WindowLostFocusEvent() = default;
    CREATE_BODY(EventType::WindowLostFocus, EventCategory::WindowEvent | EventCategory::SystemEvent)

    [[nodiscard]]
    inline std::string getEventInfoString() const override {
         return "WindowLostFocus";
    }

};

}