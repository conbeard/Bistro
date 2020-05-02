//
// Created by Connor Beard on 4/23/20.
//

#include "bpch.h"
#include "MacInput.h"

#include "Bistro/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Bistro {

    Input* Input::s_instance = new MacInput();

    bool MacInput::isKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool MacInput::isMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> MacInput::getMousePosImpl() {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float) xpos, (float) ypos };
    }

    float MacInput::getMouseXImpl() {
        auto [x, y] = getMousePosImpl();
        return x;
    }

    float MacInput::getMouseYImpl() {
        auto [x, y] = getMousePosImpl();
        return y;
    }
}
