#pragma once
#include <Window/Window.h>
#include <Windows.h>
#include <Base/MiraAPI.h>

namespace Mira {

class MIRA_API Win32Window : public WindowBase {
public:
	Win32Window();
	~Win32Window();
	static LRESULT CALLBACK messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool isOpen() const;
	HWND& getHandle();
	void handleMessages() override final;


private:
	void init() final override;
	void shutdown() final override;
	void initWndClass();
	void initWindowHandle();

private:
	std::wstring m_className;
	WNDCLASSEX m_wc;
	HINSTANCE m_instance;
	HWND m_handle;
	MSG m_msg;
};

}