#include <Window/Window.hpp>
#include <stdexcept>
#include <Events/Event.hpp>
#include <Input/KeyBoard.hpp>
#include <Logging/Log.hpp>

namespace Mira {

Window::Window(unsigned int width, unsigned int height, const std::string& title) 
	    : m_width(width), m_height(height), m_title(title) {

}

void Window::setEventCallbackFn(const EventCallBackFn& fn) {
    callback = fn;
}

Window::~Window() {

}

unsigned int Window::getWidth() const {
    return m_width;
}

unsigned int Window::getHeight() const {
    return m_height;
}
}
