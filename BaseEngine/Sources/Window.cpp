#include <Window/Window.hpp>
#include <Events/Event.hpp>
#include <Window/SDLWindow.hpp>
#include <memory>

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

std::unique_ptr<Window> Window::createWindow(int width, int height, const std::string& title) {
    return std::make_unique<SDLWindow>(width, height, title);
}

}
