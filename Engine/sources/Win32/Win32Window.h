#pragma once
#include <Windows.h>
#include <Base/MiraAPI.h>
#include <functional>
#include "WindowProperties.h"
#include <Events/Event.h>

namespace Mira {

class MIRA_API Win32Window {
public:
	Win32Window(unsigned int width = 1280u, unsigned int height = 720u, const std::wstring& title = L"Engine");
	~Win32Window();
	static LRESULT CALLBACK messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool isOpen() const;
	HWND& getHandle();
	void handleMessages();
	void close();
	void setCallBack(std::function<void(Event&)> fn);

private:
	void initWndClass();
	void initWindowHandle();

private:
	std::wstring m_className;
	WNDCLASSEX m_wc;
	HINSTANCE m_instance;
	HWND m_handle;
	MSG m_msg;

	Properties m_props;
	std::function <void(Event&)> m_callback;

};

}