#include "WIN32Window.h"

#include <windowsx.h>

#include "Mira/Event/WindowEvent.h"
#include "Mira/Event/KeyboardEvent.h"
#include "Mira/Event/MouseEvent.h"

#include "Mira/Input/InputCodes.h"

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

    auto* pWindow = reinterpret_cast<WIN32Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

    if (!pWindow) {
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    switch (msg) {
    case WM_DESTROY:
    case WM_QUIT: {
        WindowCloseEvent e;
        pWindow->m_attributes.callback(e);
        PostQuitMessage(0);
        break;
    }

	case WM_SIZE: {
		unsigned int width = LOWORD(lParam);
		unsigned int height = HIWORD(lParam);

		WindowResizeEvent e(width, height);
		pWindow->setSize(width, height);
		pWindow->m_attributes.callback(e);
		break;
	}
    
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN: {
        bool repeat = (lParam & (1 << 30)) != 0;
        
        //TODO - Modify keyboard state
        
        KeyPressEvent e(static_cast<int>(wParam), repeat);
        pWindow->m_attributes.callback(e);
        break;
    }

    case WM_KEYUP:
    case WM_SYSKEYUP: {
        
        //TODO - Modify keyboard state

        KeyReleaseEvent e(static_cast<int>(wParam));
        pWindow->m_attributes.callback(e);
        break;
    }

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN: {
        
        Mouse button;

        if (msg == WM_LBUTTONDOWN) {
            button = Mouse::Left;
        }
        else if (msg == WM_MBUTTONDOWN) {
            button = Mouse::Middle;
        }
        else if (msg == WM_RBUTTONDOWN) {
            button = Mouse::Right;
        }
        else {
            button = Mouse::X1;
        }

        //TODO - Modify Mouse state
        
        MouseButtonPressEvent e(static_cast<int>(button));
        pWindow->m_attributes.callback(e);
        break;
    }

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP: {
        
        Mouse button;

        if (msg == WM_LBUTTONUP) {
            button = Mouse::Left;
        }
        else if (msg == WM_RBUTTONUP) {
            button = Mouse::Right;
        }
        else if (msg == WM_MBUTTONUP) {
            button = Mouse::Middle;
        }
        else {
            button = Mouse::X1;
        }

        //TODO - Modify mouse state
        
        MouseButtonReleaseEvent e(static_cast<int>(button));
        pWindow->m_attributes.callback(e);
        break;
    }

    case WM_MOUSEMOVE: {
        
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);

        //TODO - Modify mouse state
        
        MouseMoveEvent e(static_cast<float>(x), static_cast<float>(y));
        pWindow->m_attributes.callback(e);
        break;
    }

    case WM_MOUSEWHEEL: {
        
        int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        
        //TODO - Modify mouse state

        MouseScrollEvent e(static_cast<float>(delta) / WHEEL_DELTA);
        pWindow->m_attributes.callback(e);
        break;
    }


    default:
        break;
    }

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

}
