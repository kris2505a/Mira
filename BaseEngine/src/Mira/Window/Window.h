#pragma once
#include <string>
#include "WindowTools.h"
#include "Mira/Core/MemoryType.hpp"

namespace Mira {

class Window {
public:
	Window(WindowAttributes attribs);
	Window() = default;
	virtual ~Window() = default;

	virtual void pollEvents() = 0;
	virtual void setWindowTitle(const std::string& title) = 0;
	
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	void setSize(unsigned int width, unsigned int height);
	virtual WindowHandle getHandle() const = 0;

public:
    bool open = true;

protected:
	WindowAttributes m_attributes;
};

}