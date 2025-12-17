#pragma once
#include <Windows.h>
#include <memory>
#include <string>

#include "Core/Core.h"

namespace Mira {

class MIRA_API Window {
public:
	Window(HINSTANCE instance);
	~Window();
	static LRESULT CALLBACK messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND& getHandle();
	void setWindowTitle(const std::wstring& str);
	bool handleMessages();
	void close();

	void create();
	void destroy();

private:
	void initWndClassEx();
	void initWindowHandle();


private:
	unsigned int m_width;
	unsigned int m_height;
	LPWSTR m_windowName;
	bool m_active;

	
	//WIN32
	LPWSTR m_className;
	WNDCLASSEX m_wc;
	HWND m_handle;
	HINSTANCE m_instance;
	MSG m_message;

};

} //NAMESPACE Mira