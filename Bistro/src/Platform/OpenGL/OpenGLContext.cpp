//
// Created by Connor Beard on 4/24/20.
//

#include "bpch.h"
#include "OpenGLContext.h"

#include "Bistro/Core.h"
#include "Bistro/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Bistro {

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_windowHandle(windowHandle) {
        B_CORE_ASSERT(windowHandle, "Window Handle in null");
    }

    void OpenGLContext::init() {
        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        B_CORE_ASSERT(status, "Failed to Initialize Glad");
    }

    void OpenGLContext::swapBuffers() {
        glfwSwapBuffers(m_windowHandle);
    }
}
