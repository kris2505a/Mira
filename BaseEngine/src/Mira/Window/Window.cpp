#include "Window.h"
#include "Mira/Logger/Logger.hpp"

namespace Mira {

Window::Window(WindowAttributes attribs)
		: m_attributes(attribs) {
	Logger::log(LogType::Info, "Creating Window: {} => {}x{}", m_attributes.title, m_attributes.width, m_attributes.height);
}

unsigned int Window::getWidth() const {
	return m_attributes.width;
}

unsigned int Window::getHeight() const {
	return m_attributes.height;
}

void Window::setSize(unsigned int width, unsigned int height) {
	m_attributes.width = width;
	m_attributes.height = height;
}


}