#include <Window/Window.hpp>
#include <stdexcept>
#include <Events/Event.hpp>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


namespace Mira {

Window::Window(unsigned int width, unsigned int height, const std::string& title) 
	    : m_width(width), m_height(height), m_title(title) {

    if (!glfwInit())
        throw std::runtime_error("Unable to init GLFW!");
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if(!m_window)
        throw std::runtime_error("Unable to create glfw Window!");

    glfwSetWindowUserPointer(m_window, this);

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        WindowResizedEvent e(width, height);
        win->m_callback(e);
    });
}

void Window::setEventCallbackFn(const EventCallBackFn& fn) {
    m_callback = fn;
}

HWND Window::getHandle() {
    return glfwGetWin32Window(m_window);
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::pollEvents() {
    glfwPollEvents();
}

unsigned int Window::getWidth() const {
    return m_width;
}

unsigned int Window::getHeight() const {
    return m_height;
}

}
