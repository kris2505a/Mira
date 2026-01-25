#include "Window.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"




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
	case WM_QUIT:
	case WM_DESTROY:
	{
		p_window->m_open = false;
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

	case WM_LBUTTONDOWN:
	{
		Mouse::buttonDown(Button::Left);
		break;
	}

	case WM_RBUTTONDOWN:
	{
		Mouse::buttonDown(Button::Right);
		break;
	}

	case WM_MBUTTONDOWN:
	{
		Mouse::buttonDown(Button::Middle);
		break;
	}

	case WM_LBUTTONUP:
	{
		Mouse::buttonUp(Button::Left);
		break;
	}

	case WM_RBUTTONUP:
	{
		Mouse::buttonUp(Button::Right);
		break;
	}

	case WM_MBUTTONUP:
	{
		Mouse::buttonUp(Button::Middle);
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
		Mouse::lockMouse(false);
		break;
	}

	
	} //switch ends

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


Window::Window(unsigned int width, unsigned int height, const std::wstring& title)
	: m_width(width), m_height(height), m_title(title) {

	m_instance = GetModuleHandle(nullptr);
	m_className = const_cast<LPWSTR>(L"WinClass");
	m_wc = {};
	m_handle = nullptr;
	m_message = {};
	m_open = true;

	initWndClassEx();
	initWindowHandle();
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
		m_title.c_str(),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_width, m_height,
		nullptr,
		nullptr,
		m_instance,
		this
	);
	ShowWindow(m_handle, SW_SHOW);
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

bool Window::isOpen() const {
	return m_open;
}

Window::~Window() {
	DestroyWindow(m_handle);
}


