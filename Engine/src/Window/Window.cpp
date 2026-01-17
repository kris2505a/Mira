#include "Window.hpp"

Window::Window(unsigned int width, unsigned int height, std::string_view title) 
	: m_width(width), m_height(height), m_title(title),  m_window(nullptr) {
	
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
}

HWND Window::handle() {
	return glfwGetWin32Window(m_window);
}

Window::~Window() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::pollEvents() {
	glfwPollEvents();
}

bool Window::open() const {
	return !glfwWindowShouldClose(m_window);
}