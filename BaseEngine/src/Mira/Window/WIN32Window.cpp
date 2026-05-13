#include "WIN32Window.h"


namespace Mira {



WIN32Window::WIN32Window(const WindowAttributes &attribs)
	: Window(attribs) {

	m_className = L"Mira Engine";

	WNDCLASSEXW wc = {};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WIN32Window::WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = m_className.c_str();

	RegisterClassExW(&wc);

	std::wstring wTitle = std::wstring(
		m_attributes.title.begin(),
		m_attributes.title.end()
	);

	RECT rect = {
		0,
		0,
		(LONG)m_attributes.width,
		(LONG)m_attributes.height
	};

	AdjustWindowRect(
		&rect,
		WS_OVERLAPPEDWINDOW,
		FALSE
	);


	m_handle = CreateWindowExW(
		0,
		m_className.c_str(),
		wTitle.c_str(),
		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);

	ShowWindow(m_handle, SW_SHOW);
	UpdateWindow(m_handle);

    SetWindowLongPtrW(m_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

}

WIN32Window::~WIN32Window() {
    DestroyWindow(m_handle);
}

void WIN32Window::pollEvents() {
	while (PeekMessageW(&m_message, nullptr, 0, 0, PM_REMOVE)) {
	    TranslateMessage(&m_message);
	    DispatchMessage(&m_message);
	}
}

void WIN32Window::setWindowTitle(const std::string& title) {
	m_attributes.title = title;

}

WindowHandle WIN32Window::getHandle() const {
	return { m_handle, GetModuleHandle(nullptr) };
}

LRESULT WIN32Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    WIN32Window* pWindow = reinterpret_cast<WIN32Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

    if (!pWindow) {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    switch (msg) {
    case WM_DESTROY:
    case WM_QUIT: {
        pWindow->open = false;
        PostQuitMessage(0);
        break;
    }
    default:
        break;
    }

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

}