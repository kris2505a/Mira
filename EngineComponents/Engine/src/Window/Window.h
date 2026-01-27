#pragma once
#include <Windows.h>
#include <memory>
#include <string>

namespace Mira {

class Window {
public:
	Window(unsigned int width, unsigned int height, const std::wstring& title);
	~Window();
	static LRESULT CALLBACK messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND& getHandle();
	void setWindowTitle(const std::wstring& str);
	bool handleMessages();
	bool isOpen() const;


private:
	void initWndClassEx();
	void initWindowHandle();


private:
	unsigned int m_width;
	unsigned int m_height;
	std::wstring m_title;
	bool m_active;
	bool m_open;


	//WIN32
	LPWSTR m_className;
	WNDCLASSEX m_wc;
	HWND m_handle;
	HINSTANCE m_instance;
	MSG m_message;
};

}