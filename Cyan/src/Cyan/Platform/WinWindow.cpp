#include "PreCompHeaders.hpp"
#include "WinWindow.hpp"
#include "Cyan/Log.hpp"

namespace Cyan {
	static bool s_GLFWInitialized = false;

	void GLFWErrorCallback(int error, const char* descr) {
		CYAN_LOG(CY_ERROR, ("GLFW Error {0} : {1}", error, descr));
	}

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

		CYAN_LOG(CY_TRACE, "Creating window: {0}, ({1}, {2})", m_data.title, m_data.width, m_data.height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			glfwSetErrorCallback(GLFWErrorCallback);
			CYAN_ASSERTS(success, "Could not init GLFW");
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {

			auto& winData = *(windowData*)glfwGetWindowUserPointer(window);
			winData.width = width;
			winData.height = height;
			WindowResizeEvent event(width, height);
			winData.eventCallBack(event);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			
			auto& winData = *(windowData*)glfwGetWindowUserPointer(window);
			windowCloseEvent event;
			winData.eventCallBack(event);
			});
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
			auto& winData = *(windowData*)glfwGetWindowUserPointer(window);
				switch (action) {
				case GLFW_PRESS: {
					keyPressedEvent event(key, 0);
					winData.eventCallBack(event);
					break;
				}
				case GLFW_RELEASE: {
					keyReleasedEvent event(key, 0);
					winData.eventCallBack(event);
					break;
				}
				case GLFW_REPEAT: {
					keyPressedEvent event(key, 1);
					winData.eventCallBack(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			auto& winData = *(windowData*)glfwGetWindowUserPointer(window);
				switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					winData.eventCallBack(event);
					break;
				}
				case GLFW_RELEASE:
					MouseButtonReleasedEvent event(button);
					winData.eventCallBack(event);
					break;
				}

			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
			auto& winData = *(windowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			winData.eventCallBack(event);

			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
			auto& winData = *(windowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)y);
			winData.eventCallBack(event);

			});
		
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
