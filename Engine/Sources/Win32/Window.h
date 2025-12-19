#pragma once
#include <Windows.h>
#include <memory>
#include <string>
#include "Core/WindowAttributes.h"
#include <functional>

#include "Signals/Signal.h"

#include "Core/Core.h"

namespace Mira {

class MIRA_API Window {
public:
	Window(HINSTANCE instance, WindowAttributes& attrib);
	~Window();
	static LRESULT CALLBACK messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND& getHandle();
	void setWindowTitle(const std::wstring& str);
	bool handleMessages();

	void init();
	void shutdown();
	void signalDestination(std::function<void(Signal&)> dest);

private:
	void initWndClassEx();
	void initWindowHandle();


private:
	unsigned int m_width;
	unsigned int m_height;
	LPWSTR m_windowName;
	bool m_active;

	WindowAttributes& r_attrib;
	std::function<void(Signal&)> m_sendSignals;

	//WIN32
	LPWSTR m_className;
	WNDCLASSEX m_wc;
	HWND m_handle;
	HINSTANCE m_instance;
	MSG m_message;

	
};

} //NAMESPACE Mira