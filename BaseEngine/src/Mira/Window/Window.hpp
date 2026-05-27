#pragma once
#include <string>
#include "WindowTools.hpp"
#include "Mira/Core/MemoryType.hpp"

namespace Mira {


class Window {
public:
	Window(WindowAttributes attribs);
	virtual ~Window() = default;


	virtual void pollEvents() = 0;
	virtual void setWindowTitle(const std::string& title) = 0;
	
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	void setSize(unsigned int width, unsigned int height);
	virtual WindowHandle getHandle() const;

	static Scope<Window> create(WindowAttributes attribs);


public:
    bool open = true;

protected:
	WindowAttributes m_attributes;
	WindowHandle m_handle;
};

}