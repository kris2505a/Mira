#include <Window/Window.hpp>
#include <stdexcept>
#include <Events/Event.hpp>


namespace Mira {

#include <windows.h>
#include <string>

std::string Window::getWin32ErrorMessage(DWORD err) {
    LPWSTR buffer = nullptr;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        err,
        0,
        (LPWSTR)&buffer,
        0,
        nullptr
    );

    if (!buffer) return "Unknown Win32 error";

    // convert wide ? narrow
    int size = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
    std::string result(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, buffer, -1, result.data(), size, nullptr, nullptr);

    LocalFree(buffer);
    return result;
}

Window::Window(unsigned int width, unsigned int height, const std::wstring& title) 
	    : m_width(width), m_height(height), m_title(title), m_instance(GetModuleHandle(nullptr)) {

    initWndClassEx();
    createWindowHandle();
    ShowWindow(m_handle, SW_SHOW);
}

void Window::initWndClassEx() {
    m_windowClass.cbSize = sizeof(WNDCLASSEXW);
    m_windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    m_windowClass.lpfnWndProc = Window::windowProcedure;
    m_windowClass.hInstance = m_instance;
    m_windowClass.lpszClassName = m_className;

    if (!RegisterClassExW(&m_windowClass)) {
        DWORD err = GetLastError();
        throw std::runtime_error("Error Registering Window Class: " + getWin32ErrorMessage(err));
    }
}

void Window::createWindowHandle() {
    m_handle = CreateWindowExW(
        0,
        m_className,
        m_title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_width, m_height,
        nullptr,
        nullptr,
        m_instance,
        this
    );

    if (!m_handle) {
        DWORD err = GetLastError();
        throw std::runtime_error("CreateWindowExW Failed: " + getWin32ErrorMessage(err));
    }
}

void Window::setEventCallbackFn(const EventCallBackFn& fn) {
    m_callback = fn;
}

HWND Window::getHandle() {
    return m_handle;
}

Window::~Window() {
    DestroyWindow(m_handle);
}

void Window::pollEvents() {
    MSG msg;
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

unsigned int Window::getWidth() const {
    return m_width;
}

unsigned int Window::getHeight() const {
    return m_height;
}

LRESULT CALLBACK Window::windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    Window* window = nullptr;

    if (msg == WM_NCCREATE) {
        auto* cs = reinterpret_cast<CREATESTRUCT*>(lparam);
        window = reinterpret_cast<Window*>(cs->lpCreateParams);

        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);

        // (optional but nice)
        window->m_handle = hwnd;
    }
    else {
        window = reinterpret_cast<Window*>(
            GetWindowLongPtr(hwnd, GWLP_USERDATA)
        );
    }

    switch (msg)
    {
    case WM_DESTROY:
    case WM_QUIT:
    {
        PostQuitMessage(0);
        WindowClosedEvent e;
        window->m_callback(e);
        break;
    }

    }

    
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

}
