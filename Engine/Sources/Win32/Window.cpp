#include <PreCompHeader.h>
#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"

#include "Logger/Log.h"
#include "Signals/KeyboardSignal.h"
#include "Signals/MouseSignal.h"
#include "Signals/WindowSignal.h"
#include <backends/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Mira {

//forward declaration for imgui


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

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam)) {
		return true;
	}

	switch (msg) {
	case WM_DESTROY:
	{
		WindowCloseSignal s;
		p_window->m_sendSignals(s);
		PostQuitMessage(0);
		break;
	}

	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{

		const bool wasDown = (lParam & (1 << 30)) != 0;
		if (!wasDown)
			Keyboard::keyPressed(wParam);
		KeyDownSignal s(static_cast <Key> (wParam));
		p_window->m_sendSignals(s);
		break;
	}

	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		Keyboard::keyReleased(wParam);
		KeyUpSignal s(static_cast <Key> (wParam));
		p_window->m_sendSignals(s);
		break;
	}

	case WM_LBUTTONDOWN:
	{
		Mouse::buttonDown(Button::MouseLeft);
		MouseButtonDownSignal s(Button::MouseLeft);
		p_window->m_sendSignals(s);
		break;
	}

	case WM_RBUTTONDOWN:
	{
		Mouse::buttonDown(Button::MouseRight);
		MouseButtonDownSignal s(Button::MouseRight);
		p_window->m_sendSignals(s);
		break;
	}
	
	case WM_MBUTTONDOWN:
	{
		Mouse::buttonDown(Button::MouseMiddle);
		MouseButtonDownSignal s(Button::MouseMiddle);
		p_window->m_sendSignals(s);
		break;
	}

	case WM_LBUTTONUP:
	{
		Mouse::buttonUp(Button::MouseLeft);
		MouseButtonUpSignal s(Button::MouseLeft);
		p_window->m_sendSignals(s);
		break;
	}

	case WM_RBUTTONUP:
	{
		Mouse::buttonUp(Button::MouseRight);
		MouseButtonUpSignal s(Button::MouseRight);
		p_window->m_sendSignals(s);
		break;
	}

	case WM_MBUTTONUP:
	{
		Mouse::buttonUp(Button::MouseMiddle);
		MouseButtonUpSignal s(Button::MouseMiddle);
		p_window->m_sendSignals(s);
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

		MouseMoveSignal s(pts.x, pts.y);
		p_window->m_sendSignals(s);
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
		WindowResizeSignal s;
		p_window->m_sendSignals(s);

		RECT wr;
		GetWindowRect(p_window->m_handle, &wr);
		if (wParam != SIZE_MINIMIZED) {
			p_window->r_attrib.width = wr.right - wr.left;
			p_window->r_attrib.height = wr.bottom - wr.top;
		}
		p_window->r_attrib.maximized = (wParam == SIZE_MAXIMIZED);
		break;
	} 	

	} //switch ends

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


Window::Window(HINSTANCE instance, WindowAttributes& attrib)
	: m_instance(instance), r_attrib(attrib) {

	m_width = r_attrib.width;
	m_height = r_attrib.height;
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

	m_handle = CreateWindowEx(
		0,
		m_className,
		m_windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		r_attrib.width, r_attrib.height,
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
		TranslateMessage(&m_message);
		DispatchMessage(&m_message);
	}
	return true;
}

void Window::init() {
	initWndClassEx();
	initWindowHandle();

	int showCmd = 0;
	if (r_attrib.maximized)
		showCmd = SW_SHOWMAXIMIZED;
	else
		showCmd = SW_SHOW;
	ShowWindow(m_handle, showCmd);
	m_active = true;
	MIRA_LOG(LOG_INFO, "Window Initialized");
}

void Window::shutdown() {
	DestroyWindow(m_handle);
	m_active = false;
	MIRA_LOG(LOG_INFO, "Window ShutDown");
}

void Window::signalDestination(std::function<void(Signal&)> dest) {
	m_sendSignals = dest;
}

Window::~Window() {
	if (m_active) {
		shutdown();
	}
}


} //NAMESPACE Mira
