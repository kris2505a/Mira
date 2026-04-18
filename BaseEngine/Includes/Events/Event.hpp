#pragma once
#include <string>
#include <format>

namespace Mira {

enum EventType {
	KeyPressed,
	KeyReleased,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScrolled,
	WindowClosed,
	WindowResized
};

#define EVENT_CLASS_TYPE(type) \
    static EventType getStaticType() { return EventType::type; } \
    virtual EventType getEventType() const override { return getStaticType(); } \
    virtual const char* getName() const override { return #type; }

class Event {
public:
	bool Handled = false;

    virtual ~Event() = default;
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual std::string toString() const {
        return getName();
    }
};

class KeyEvent : public Event {
public:
    inline int getKey() const {
        return m_key;
    }

protected:
    KeyEvent(int key) : m_key(key) {}
    int m_key;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int key, bool repeated) 
            : KeyEvent(key), m_repeated(repeated) {}

    inline bool isRepeated() const { return m_repeated; }
 
    std::string toString() const override {
        return std::format("KeyPressedEvent: {} (Repeat = {})", m_key, m_repeated);
    }
 
    EVENT_CLASS_TYPE(KeyPressed)

private:
    bool m_repeated;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int key)
            : KeyEvent(key) {}

    std::string toString() const override {
        return std::format("KeyReleasedEvent: {}", m_key);
    }

    EVENT_CLASS_TYPE(KeyReleased);
};

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) 
            : m_xPos(x), m_yPos(y) {}

    inline float getXPos() const { return m_xPos; }
    inline float getYPos() const { return m_yPos; }

    std::string toString() const override {
        return std::format("MouseMovedEvent: {}, {}", m_xPos, m_yPos);
    }

    EVENT_CLASS_TYPE(MouseMoved);

private:
    float m_xPos;
    float m_yPos;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xOffset, float yOffset)
            : m_xOffset(xOffset), m_yOffset(yOffset){}

    inline float getXOffset() const { return m_xOffset; }
    inline float getYOffset() const { return m_yOffset; }

    std::string toString() const override {
        return std::format("MouseScrolledEvent: {}, {}", m_xOffset, m_yOffset);
    }

    EVENT_CLASS_TYPE(MouseScrolled);
private:
    float m_xOffset;
    float m_yOffset;
};

class MouseButtonEvent : public Event {
public:
    inline int getButton() const { return m_button; }
protected:
    MouseButtonEvent(int button)
            : m_button(button) {}
    int m_button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}
    std::string toString() const override {
        return std::format("MouseButtonPressedEvent: {}", m_button);
    }
    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

    std::string toString() const override {
         return std::format("MouseButtonReleasedEvent: {}", m_button);
    }
    EVENT_CLASS_TYPE(MouseButtonReleased);
};

class WindowClosedEvent : public Event {
public:
    WindowClosedEvent() = default;
    std::string toString() const override {
        return "WindowClosedEvent";
    }

    EVENT_CLASS_TYPE(WindowClosed);
};

class WindowResizedEvent : public Event {
public:
    WindowResizedEvent(int width, int height)
            : m_width(width), m_height(height) {}

    std::string toString() const override {
        return std::format("WindowResizedEvent: {}x{}", m_width, m_height);
    }

    EVENT_CLASS_TYPE(WindowResized);
private:
    int m_width;
    int m_height;
};

}
