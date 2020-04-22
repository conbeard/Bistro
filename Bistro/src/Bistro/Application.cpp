//
// Created by Connor Beard on 4/20/20.
//
#include "bpch.h"
#include "Application.h"
#include "Log.h"

#include <GLFW/glfw3.h>

namespace Bistro {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() {
        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application() = default;

    void Application::Run() {
        B_CORE_ASSERT(true, "Test")

        while (m_running) {
            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event &e) {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        B_CORE_TRACE("{0}", e);
    }

    bool Application::onWindowClose(WindowCloseEvent) {
        m_running = false;
        return true;
    }
}
