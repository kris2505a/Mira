#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Input/Input.h"

#include "Logger/Log.h"

#include <windowsx.h>

namespace Mira {

LRESULT CALLBACK Window::messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	Window* p_window = nullptr;


	if (msg == WM_NCCREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		p_window = static_cast<Window*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_window));
	}
	else {
		p_window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	switch (msg) {
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{

		const bool wasDown = (lParam & (1 << 30)) != 0;
		if (!wasDown)
			Keyboard::keyPressed(wParam);
		break;
	}

	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		Keyboard::keyReleased(wParam);
		break;
	}

	case WM_XBUTTONDOWN:
	{
		Mouse::buttonDown(VK_MBUTTON);
		break;
	}

	case WM_XBUTTONUP:
	{
		Mouse::buttonUp(VK_MBUTTON);
		break;
	}

	case WM_MOUSEMOVE:
	{
		POINTS pts = MAKEPOINTS(lParam);

		if (pts.x >= 0 && pts.x <= p_window->m_width && pts.y >= 0 && pts.y <= p_window->m_height) {
			Mouse::move(pts.x, pts.y);
			if (!Mouse::isInWindow()) {
				SetCapture(p_window->m_handle);
				Mouse::inWindow();
			}
		}
		else {
			if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
				Mouse::move(pts.x, pts.y);
			}
			else {
				ReleaseCapture();
				Mouse::offWindow();
			}
		}
		break;
	}

	case WM_MOUSEWHEEL:
	{
		Mouse::scroll(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	}

	case WM_KILLFOCUS:
	{
		Keyboard::clearState();
		break;
	}

	case WM_SIZE:
	{
		if (!wParam == SIZE_MINIMIZED) {
			p_window->m_width = LOWORD(lParam);
			p_window->m_height = HIWORD(lParam);
		}
		break;
	} 

	} //switch ends

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


Window::Window(HINSTANCE instance)
	: m_instance(instance) {

	m_width = 1920;
	m_height = 1080;
	m_windowName = const_cast <LPWSTR> (L"Mira Engine");
	m_className = const_cast<LPWSTR>(L"WinClass");
	m_wc = {};
	m_handle = nullptr;
	m_message = {};
	m_active = true;

}

void Window::initWndClassEx() {

	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.style = CS_OWNDC;
	m_wc.lpfnWndProc = Window::messageProc;
	m_wc.cbClsExtra = 0;
	m_wc.cbWndExtra = 0;
	m_wc.hInstance = m_instance;
	m_wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	m_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wc.lpszMenuName = nullptr;
	m_wc.lpszClassName = m_className;
	m_wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassEx(&m_wc);
}

void Window::initWindowHandle() {

	unsigned int xPos = (1920 - m_width) / 2;
	unsigned int yPos = (1080 - m_height) / 2;

	m_handle = CreateWindowEx(
		0,
		m_className,
		m_windowName,
		WS_OVERLAPPEDWINDOW,
		xPos, yPos,
		m_width, m_height,
		nullptr,
		nullptr,
		m_instance,
		this
	);
}



HWND& Window::getHandle() {
	return m_handle;
}

void Window::setWindowTitle(const std::wstring& str) {
	SetWindowText(m_handle, str.c_str());
}

bool Window::handleMessages() {
	while (PeekMessage(&m_message, nullptr, 0, 0, PM_REMOVE)) {

		if (m_message.message == WM_QUIT)
			return false;

		TranslateMessage(&m_message);
		DispatchMessage(&m_message);
	}
	return true;
}

void Window::create() {
	initWndClassEx();
	initWindowHandle();
	ShowWindow(m_handle, SW_SHOWMAXIMIZED);
	m_active = true;
	MIRA_LOG(LOG_INFO, "Window Created");
}

void Window::destroy() {
	DestroyWindow(m_handle);
	m_active = false;
	MIRA_LOG(LOG_INFO, "Window Destroyed");
}

Window::~Window() {
	if (m_active) {
		destroy();
	}
}


} //NAMESPACE Mirat
