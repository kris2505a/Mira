#pragma once
#include <helpers/mi_types.hpp>

namespace mira::engine {

struct Event {
    bool handled{ false };
    virtual ~Event() = default;
};

class EventDispatcher {
public:
    EventDispatcher(Event& event)
        : rEvent(event) {}

    template<typename T, typename  F>
    bool dispatch(const F& func) {
        
        if (rEvent.handled) {
            return false;
        }

        if (auto* event = dynamic_cast<T*>(&rEvent)) {
            rEvent.handled |= func(*event);
            return true;
        }
        return false;
    }


private:
    Event& rEvent;
};


struct KeyEvent : public Event {
    const core::u32 key;
    KeyEvent(core::u32 _key)
        : key(_key) {}
};

struct KeyPressEvent : public KeyEvent {
    const bool repeat;
    KeyPressEvent(core::u32 _key, bool _repeat)
        : KeyEvent(_key), repeat(_repeat) {}
};

struct KeyReleaseEvent : public KeyEvent {
    KeyReleaseEvent(core::u32 _key)
        : KeyEvent(_key) {}
};

struct MouseButtonEvent : public Event {
    const core::u32 button;
    MouseButtonEvent(core::u32 _button)
        : button(_button) {}
};

struct MouseButtonPressEvent : public MouseButtonEvent {
    const bool held;
    MouseButtonPressEvent(core::u32 _button, bool _held)
        : MouseButtonEvent(_button), held(_held) {}
};

struct MouseButtonReleaseEvent : public MouseButtonEvent {
    MouseButtonReleaseEvent(core::u32 _button)
        : MouseButtonEvent(_button) {}
};

struct MouseMoveEvent : public Event {
    const core::f32 x;
    const core::f32 y;

    MouseMoveEvent(core::f32 _x, core::f32 _y)
        : x(_x), y(_y) {}
};

struct MouseScrollEvent : public Event {
    const core::f32 delta;
    MouseScrollEvent(core::f32 _delta) 
        : delta(_delta) {}
};

struct WindowResizeEvent : public Event {
    const core::f32 width;
    const core::f32 height;

    WindowResizeEvent(core::f32 _width, core::f32 _height)
        : width(_width), height(_height) {}
};

struct WindowLostFocus : public Event {
    WindowLostFocus() = default;
};

}
