#pragma once
#include <string>

struct Properties {
	unsigned int width = 0;
	unsigned int height = 0;
	std::wstring title = L"None";
	std::wstring className = L"None";
	bool open = false;
	bool fullScreen = false;
	bool vSync = false;
};