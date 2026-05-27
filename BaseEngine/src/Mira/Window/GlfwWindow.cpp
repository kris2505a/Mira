#include "MiraPch.hpp"
#include "GlfwWindow.hpp"
#include "Mira/Logger/Logger.hpp"
#include "Mira/Core/Assert.hpp"


#include "Mira/Event/KeyboardEvent.hpp"
#include "Mira/Event/MouseEvent.hpp"
#include "Mira/Event/WindowEvent.hpp"

namespace Mira {

GlfwWindow::GlfwWindow(WindowAttributes attribs) : Window(attribs) {

    if (s_windowReferences == 0) {
        glfwInit();
    }

    s_windowReferences++;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(
        static_cast<int>(m_attributes.width), 
        static_cast<int>(m_attributes.height),
        m_attributes.title.c_str(),
        nullptr,
        nullptr
    );

    
    MIRA_ASSERT(m_window, "Failed to create window!");
    
    m_handle.window = static_cast<void*>(m_window);

    glfwSetWindowUserPointer(m_window, this);


    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height){
        auto& callback = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_attributes.callback;
        WindowResizeEvent e(width, height);
        callback(e);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window){
        auto& callback = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_attributes.callback;
        WindowCloseEvent e;
        callback(e);
    });

    glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focus){
        if (focus == GLFW_FALSE) {
            auto& callback = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_attributes.callback;
            WindowLostFocusEvent e;
            callback(e);
        }
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto& callback = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_attributes.callback;
    
        switch (action) {
        case GLFW_PRESS: {
            KeyPressEvent e(key, false);
            callback(e);
            break;
        }

        case GLFW_RELEASE: {
            KeyReleaseEvent e(key);
            callback(e);
            break;
        }

        case GLFW_REPEAT: {
            KeyPressEvent e(key, true);
            callback(e);
            break;
        }
    
        }
        
    });


    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
        auto& callback = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_attributes.callback;
        
        switch (action) {
        case GLFW_PRESS: {
            MouseButtonPressEvent e(button);
            callback(e);
            break;
        }

        case GLFW_RELEASE: {
            MouseButtonReleaseEvent e(button);
            callback(e);
            break;
        }
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
        auto& callback = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_attributes.callback;
        MouseScrollEvent e(static_cast<float>(yoffset));
        callback(e);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
        auto& callback = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window))->m_attributes.callback;
        MouseMoveEvent e(static_cast<float>(x), static_cast<float>(y));
        callback(e);
    });
     

}

void GlfwWindow::pollEvents() {
    glfwPollEvents();
}

void GlfwWindow::setWindowTitle(const std::string& title) {
    
}


GlfwWindow::~GlfwWindow() {
    glfwDestroyWindow(m_window);
    s_windowReferences--;

    if (s_windowReferences == 0) {
        glfwTerminate();
    }
}

}