#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <string_view>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

class Window {
public:
	Window(unsigned int width, unsigned int height, std::string_view title);
	~Window();
	void pollEvents();
	HWND handle();
	bool open() const;

private:
	GLFWwindow* m_window;
	unsigned int m_width;
	unsigned int m_height;
	std::string m_title;
};