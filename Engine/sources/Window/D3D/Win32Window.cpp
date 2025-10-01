#include <MiraPreCompHeader.h>
#include "Win32Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"

namespace Mira {
Win32Window::Win32Window() {
	init();
}

Win32Window::~Win32Window() {
	shutdown();
}

LRESULT CALLBACK Win32Window::messageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	Win32Window* p_window = nullptr;

	if (msg == WM_NCCREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		p_window = static_cast<Win32Window*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_window));
	}
	else {
		p_window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	switch (msg) {
	case WM_DESTROY:
	{
		if (p_window)
			p_window->m_properties.open = false;
		PostQuitMessage(0);
	}break;


	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		if (!(lParam & 0x40000000) || Keyboard::repeatStatus()) {
			Keyboard::keyPressed(wParam);
			KeyPressedEvent e(static_cast <int> (wParam));
			p_window->m_callback(e);
		}

		break;
	}

	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		Keyboard::keyReleased(wParam);
		KeyReleasedEvent e(static_cast <int> (wParam));
		p_window->m_callback(e);
		break;
	}

	case WM_XBUTTONDOWN:
	{	
		unsigned int button = GET_XBUTTON_WPARAM(wParam);
		Mouse::buttonDown(button);
		MouseButtonPressEvent e(static_cast <int> (button));
		p_window->m_callback(e);
		break;
	}

	case WM_XBUTTONUP:
	{
		unsigned int button = GET_XBUTTON_WPARAM(wParam);
		Mouse::buttonUp(button);
		MouseButtonReleaseEvent e(static_cast <int> (button));
		p_window->m_callback(e);
		break;
	}

	case WM_MOUSEMOVE:
	{
		POINTS pts = MAKEPOINTS(lParam);

		if (pts.x >= 0 && pts.x <= p_window->m_properties.width && pts.y >= 0 && pts.y <= p_window->m_properties.height) {
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
		MouseMoveEvent e(pts.x, pts.y);
		p_window->m_callback(e);
		break;
	}

	case WM_MOUSEWHEEL:
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		Mouse::scroll(delta);
		float yOffset = static_cast <float> (delta) / WHEEL_DELTA;
		MouseScrollEvent e(0.0f, yOffset);
		p_window->m_callback(e);
		break;
	}

	case WM_KILLFOCUS:
	{
		Keyboard::clearState();
		break;
	}

	} //switch ends

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Win32Window::isOpen() const {
	return m_properties.open;
}

HWND& Win32Window::getHandle() {
	return m_handle;
}

void Win32Window::handleMessages(){
	while (PeekMessage(&m_msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}
}

void Win32Window::init() {
	m_instance = GetModuleHandle(nullptr);
	m_className = const_cast<LPWSTR>(L"WinClass");
	initWndClass();
	initWindowHandle();
	ShowWindow(m_handle, SW_SHOW);
}

void Win32Window::initWndClass() {
	m_className = const_cast<LPWSTR>(L"WinClass");
	m_wc.cbSize = sizeof(WNDCLASSEX);
	m_wc.style = CS_OWNDC;
	m_wc.lpfnWndProc = Win32Window::messageProc;
	m_wc.cbClsExtra = 0;
	m_wc.cbWndExtra = 0;
	m_wc.hInstance = m_instance;
	m_wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	m_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wc.lpszMenuName = nullptr;
	m_wc.lpszClassName = m_className.c_str();
	m_wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassEx(&m_wc);
}

void Win32Window::initWindowHandle() {
	std::wstring name = std::wstring(m_properties.title.begin(), m_properties.title.end());

	m_handle = CreateWindowEx(
		0,
		m_className.c_str(),
		name.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_properties.width, m_properties.height,
		nullptr,
		nullptr,
		m_instance,
		this
	);
}

void Win32Window::shutdown() {
	DestroyWindow(m_handle);
}

}