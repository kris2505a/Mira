#pragma once
#include <Core/Core.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <Windows.h>
#include <functional>
#include <Events/Event.hpp>

namespace Mira {

class Window {

    using EventCallBackFn = std::function<void(Event&)>;
public:
	Window(unsigned int width = 1280u, unsigned int height = 720u, const std::string& title = "Engine");
	~Window();
	HWND getHandle();
	void pollEvents();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setEventCallbackFn(const EventCallBackFn& fn);

private:
	GLFWwindow* m_window    = nullptr;
	unsigned int m_width    = 1280u;
	unsigned int m_height   = 720u;
	std::string m_title     = "";
    EventCallBackFn m_callback;

};

}
