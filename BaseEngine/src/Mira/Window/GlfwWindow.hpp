#pragma once
#include "Window.hpp"
#include <GLFW/glfw3.h>

namespace Mira {

class GlfwWindow : public Window {
public:
    GlfwWindow(WindowAttributes attribs);
    ~GlfwWindow();

    void pollEvents() override;
    void setWindowTitle(const std::string& title) override;
    

private:
    GLFWwindow* m_window;
    inline static uint32_t s_windowReferences = 0;
};

}