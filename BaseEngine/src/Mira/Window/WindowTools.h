#pragma once
#include <Windows.h>
#include <string>
#include <functional>
#include <utility>
#include "Mira/Event/Event.h"

namespace Mira {

struct WindowHandle {
	HWND handle;
	HINSTANCE instance;
};

struct WindowAttributes {
	unsigned int width;
	unsigned int height;
	std::string title;
    std::function<void(Event&)> callback;

    WindowAttributes(int w, int h, std::string  t, const std::function<void(Event&)>& cb)
        : width(w), height(h), title(std::move(t)), callback(cb) {}
};

}