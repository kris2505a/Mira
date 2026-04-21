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
	Window(unsigned int width, unsigned int height, const std::wstring& title);
	~Window();
	HWND getHandle();
	void pollEvents();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setEventCallbackFn(const EventCallBackFn& fn);
    static LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
    //private methods
    void initWndClassEx();
    void createWindowHandle();
    std::string getWin32ErrorMessage(DWORD err);

private:
    //Window stuff
	unsigned int m_width    = 1280u;
	unsigned int m_height   = 720u;
	std::wstring m_title    = L"Mira Engine";
    EventCallBackFn m_callback;

private:
    //Win32 stuff
    HINSTANCE m_instance;
    HWND m_handle;
    WNDCLASSEXW m_windowClass   = {};
    const wchar_t* m_className  = L"Mira_Window";
};

}
