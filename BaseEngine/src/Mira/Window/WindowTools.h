#pragma once
#include <Windows.h>
#include <string>
#include <format>

namespace Mira {

struct WindowHandle {
	HWND handle;
	HINSTANCE instance;
};

struct WindowAttributes {
	unsigned int width;
	unsigned int height;
	std::string title;
};

}