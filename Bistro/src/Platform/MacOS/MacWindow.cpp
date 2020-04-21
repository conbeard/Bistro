//
// Created by Connor Beard on 4/21/20.
//

#include "bpch.h"
#include "MacWindow.h"
#include "Log.h"

namespace Bistro {

    static bool s_GLFWInitialized = false;

    Window* Window::create(const WindowProps& props) {
        return new MacWindow(props);
    }

    MacWindow::MacWindow(const WindowProps &props) {
        init(props);
    }

    MacWindow::~MacWindow() {
        shutdown();
    }

    void MacWindow::init(const WindowProps &props) {
        m_data.title = props.m_title;
        m_data.width = props.m_width;
        m_data.height = props.m_height;

        B_CORE_INFO("Creating Window {0} ({1}, {2})", props.m_title, props.m_width, props.m_height);

        if (!s_GLFWInitialized) {
            int success = glfwInit();
            B_CORE_ASSERT(success, "Could not initialize GLFW!");

            s_GLFWInitialized = true;
        }

        m_window = glfwCreateWindow((int) m_data.width, (int) m_data.height, m_data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);
    }

    void MacWindow::shutdown() {
        glfwDestroyWindow(m_window);
    }

    void MacWindow::onUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void MacWindow::setVSync(bool enabled) {
        if (enabled) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        m_data.vSync = enabled;
    }

    bool MacWindow::isVSync() const {
        return m_data.vSync;
    }

}
