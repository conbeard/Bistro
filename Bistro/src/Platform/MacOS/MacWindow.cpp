//
// Created by Connor Beard on 4/21/20.
//

#include "bpch.h"
#include "MacWindow.h"
#include "Log.h"

#include "Bistro/Events/Event.h"
#include "Bistro/Events/KeyEvent.h"
#include "Bistro/Events/MouseEvent.h"
#include "Bistro/Events/ApplicationEvent.h"

#include <glad/glad.h>

namespace Bistro {

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* message) {
        B_CORE_ERROR("GLFW Error ({0}): {1}", error, message);
    }

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

            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        m_window = glfwCreateWindow(
            (int) m_data.width,
            (int) m_data.height,
            m_data.title.c_str(),
            nullptr, nullptr
        );

        glfwMakeContextCurrent(m_window);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        B_CORE_ASSERT(status, "Failed to Initialize Glad")

        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            data.width = width;
            data.height = height;

            WindowResizeEvent event(width, height);
            data.callback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.callback(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int keyCode, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            if (action == GLFW_PRESS) {
                KeyPressedEvent event(keyCode, 0);
                data.callback(event);
            } else if (action == GLFW_RELEASE) {
                KeyReleasedEvent event(keyCode);
                data.callback(event);
            } else if (action == GLFW_REPEAT) {
                KeyPressedEvent event(keyCode, 1);
                data.callback(event);
            }
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            if (action == GLFW_PRESS) {
                MouseButtonPressedEvent event(button);
                data.callback(event);
            } else if (action == GLFW_RELEASE) {
                MouseButtonReleasedEvent event(button);
                data.callback(event);
            }

        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float) xpos, (float) ypos);
            data.callback(event);
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float) xOffset, (float) yOffset);
            data.callback(event);
        });
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
