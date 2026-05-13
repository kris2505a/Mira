#pragma once
#include "Window.h"

namespace Mira {

class WIN32Window : public Window {
public:
	WIN32Window(const WindowAttributes &attribs);
	~WIN32Window() override;


	void pollEvents() override;
	void setWindowTitle(const std::string& title) override;
	[[nodiscard]] WindowHandle getHandle() const override;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND m_handle;
	std::wstring m_className;
	MSG m_message{};
};

}