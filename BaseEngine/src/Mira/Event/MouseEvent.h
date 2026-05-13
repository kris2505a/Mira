#pragma once
#include "Event.h"
#include <format>


namespace Mira {

class MouseButtonEvent : public Event {
public:
    [[nodiscard]]
    inline int getButton() const {
        return m_button;
    }

protected:
    MouseButtonEvent(int button) : m_button(button) {}

private:
    int m_button;
};

class MouseButtonPressEvent : public MouseButtonEvent {
public:
    MouseButtonPressEvent(int button) : MouseButtonEvent(button) {}
    CREATE_BODY(EventType::MouseButtonPressed, EventCategory::MouseEvent | EventCategory::InputEvent)

    [[nodiscard]]
    inline std::string getEventInfoString() const override {
        return std::format("MouseButtonPressed: {}", getButton());
    }

};

class MouseButtonReleaseEvent : public MouseButtonEvent {
public:
    MouseButtonReleaseEvent(int button) : MouseButtonEvent(button) {}
    CREATE_BODY(EventType::MouseButtonReleased, EventCategory::MouseEvent | EventCategory::InputEvent);

    [[nodiscard]]
    inline std::string getEventInfoString() const override {
        return std::format("MouseButtonReleased: {}", getButton());
    }
};

class MouseMoveEvent : public Event {
public:
    MouseMoveEvent(float x, float y) : m_xPosition(x), m_yPosition(y) {}

    CREATE_BODY(EventType::MouseMoved, EventCategory::MouseEvent | EventCategory::InputEvent)

    [[nodiscard]]
    inline std::string getEventInfoString() const override {
        return std::format("MouseMoved: {}, {}", m_xPosition, m_yPosition);
    }

private:
    float m_xPosition;
    float m_yPosition;
};

class MouseScrollEvent : public Event {
public:
    MouseScrollEvent(float offset) : m_offset(offset) {}

    CREATE_BODY(EventType::MouseScrolled, EventCategory::MouseEvent | EventCategory::InputEvent)

    [[nodiscard]]
    inline std::string getEventInfoString() const override {
        return std::format("MouseScrolled: {}", m_offset);
    }

    inline float getOffset() const {
        return m_offset;
    }

private:
    float m_offset;
};

}
