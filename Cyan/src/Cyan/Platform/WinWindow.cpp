#include "PreCompHeaders.hpp"
#include "WinWindow.hpp"
#include "Cyan/Log.hpp"

namespace Cyan {
	static bool s_GLFWInitialized = false;

	GWindow* GWindow::createWindow(const windowAttributes& attrib) {
		return new winWindow(attrib);
	}

	winWindow::winWindow(const windowAttributes& attrib) {
		init(attrib);
	}

	winWindow::~winWindow() {

	}

	void winWindow::init(const windowAttributes& attrib) {
		m_data.title = attrib.windowTitle;
		m_data.width = attrib.windowWidth;
		m_data.height = attrib.windowHeight;

		CYAN_LOG(CY_TRACE, "Creating window {0}, ({1}, {2})", m_data.title, m_data.width, m_data.height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			CYAN_ASSERTS(success, "Could not init GLFW");
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);
	}

	void winWindow::shutDown() {
		glfwDestroyWindow(m_window);
	}

	void winWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void winWindow::setVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_data.vSync = enabled;
	}

	bool winWindow::isVSync() const {
		return m_data.vSync;
	}
}
