#include "mi_window.hpp"
#include <windowsx.h>

namespace mira::core {
Window::Window() {

    mWindowHandles.instance = GetModuleHandleA(nullptr);

    WNDCLASSEXA wc = {};
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Window::windowProc;
    wc.hInstance = mWindowHandles.instance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = mclassName.c_str();

    RegisterClassExA(&wc);

    RECT rect = {
        0,
        0,
        (LONG)mWidth,
        (LONG)mHeight
    };

    AdjustWindowRect(
        &rect,
        WS_OVERLAPPEDWINDOW,
        FALSE
    );

    mWindowHandles.window = CreateWindowExA(
    0,
    mclassName.c_str(),
    mWindowName.c_str(),
    WS_OVERLAPPEDWINDOW,

    CW_USEDEFAULT,
    CW_USEDEFAULT,
    rect.right - rect.left,
    rect.bottom - rect.top,
    nullptr,
    nullptr,
    mWindowHandles.instance,
    nullptr
);

    ShowWindow(mWindowHandles.window, SW_SHOW);
    UpdateWindow(mWindowHandles.window);

    SetWindowLongPtrW(mWindowHandles.window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

}

LRESULT Window::windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        auto* pWindow = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

    if (!pWindow) {
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    switch (msg) {
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }

	case WM_SIZE: {
		unsigned int width = LOWORD(lParam);
		unsigned int height = HIWORD(lParam);
        if (pWindow->mCallbacks.resize)
            pWindow->mCallbacks.resize(width, height);
		break;
	}

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN: {
        bool repeat = (lParam & (1 << 30)) != 0;
        if (pWindow->mCallbacks.key)
            pWindow->mCallbacks.key(static_cast<u32>(wParam), repeat, true);
        break;
    }

    case WM_KEYUP:
    case WM_SYSKEYUP: {
        if (pWindow->mCallbacks.key)
            pWindow->mCallbacks.key(static_cast<u32>(wParam), false, false);
        break;
    }

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN: {
        
        u32 mouse;
        if (msg == WM_LBUTTONDOWN) {
            mouse = 1;
        }
        else if (msg == WM_MBUTTONDOWN) {
            mouse = 2;    
        }
        else if (msg == WM_RBUTTONDOWN) {
            mouse = 3;
        }
        else {
            mouse = 0;
        }
        if (pWindow->mCallbacks.mouseButton)
            pWindow->mCallbacks.mouseButton(mouse, true);
        break;
    }

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP: {

        u32 mouse;
        if (msg == WM_LBUTTONUP) {
            mouse = 1;
        }
        else if (msg == WM_MBUTTONUP) {
            mouse = 2;    
        }
        else if (msg == WM_RBUTTONUP) {
            mouse = 3;
        }
        else {
            mouse = 0;
        }
        if (pWindow->mCallbacks.mouseButton)
            pWindow->mCallbacks.mouseButton(mouse, false);
        break;
    }

    case WM_MOUSEMOVE: {

        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
        if (pWindow->mCallbacks.mouseMove)
            pWindow->mCallbacks.mouseMove(static_cast<f32>(x), static_cast<f32>(y));
        break;
    }

    case WM_MOUSEWHEEL: {
        int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (pWindow->mCallbacks.mouseScroll)
            pWindow->mCallbacks.mouseScroll(delta);
        break;
    }
    
    case WM_KILLFOCUS: {
        if (pWindow->mCallbacks.lostFocus)
            pWindow->mCallbacks.lostFocus();
        break;
    }

    default:
        break;
    }

	return DefWindowProcA(hwnd, msg, wParam, lParam);

}

auto Window::setKeyCallback(Window::KeyCallback key) -> void {
    mCallbacks.key = key;
}

auto Window::setMouseButtonCallback(Window::MouseButtonCallback button) -> void {
    mCallbacks.mouseButton = button;
}

auto Window::setMouseMoveCallback(Window::MouseMoveCallback move) -> void {
    mCallbacks.mouseMove = move;
}

auto Window::setMouseScrollCallback(Window::MouseScrollCallback scroll) -> void {
    mCallbacks.mouseScroll = scroll;
}

auto Window::setResizeCallback(Window::ResizeCallback resize) -> void {
    mCallbacks.resize = resize;
}

auto Window::setLostFocusCallback(Window::LostFocusCallback lostFocus) -> void {
    mCallbacks.lostFocus = lostFocus;
}


auto Window::pollEvents() -> bool {
    while (PeekMessageA(&mWindowHandles.message, nullptr, 0, 0, PM_REMOVE)) {
        if (WM_QUIT == mWindowHandles.message.message || WM_DESTROY == mWindowHandles.message.message) {
            return false; 
        }
        TranslateMessage(&mWindowHandles.message);
        DispatchMessage(&mWindowHandles.message);
    }
    return true;
}

auto Window::getWin32Handle() const -> HWND {
    return mWindowHandles.window;
}

Window::~Window() {
    DestroyWindow(mWindowHandles.window);
}
}
