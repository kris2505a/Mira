#pragma once
#include <Core/Core.hpp>
#include <string>
#include <Windows.h>
#include <functional>
#include <Events/Event.hpp>
#include <Windows.h>

namespace Mira {

class Window {

    using EventCallBackFn = std::function<void(Event&)>;
public:
	Window(unsigned int width = 1280u, unsigned int height = 720u, const std::string& title = "Test Rig");
	~Window();
	virtual HWND getHandle() = 0;
	virtual void pollEvents() = 0;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setEventCallbackFn(const EventCallBackFn& fn);

private:
    //Window stuff
	unsigned int m_width;
	unsigned int m_height;
	std::string m_title;

protected:
    EventCallBackFn callback;

};

}
