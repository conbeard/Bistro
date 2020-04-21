//
// Created by Connor Beard on 4/20/20.
//
#include "bpch.h"
#include "Application.h"
#include "Log.h"

namespace Bistro {
    Application::Application() {
        m_window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application() = default;

    void Application::Run() {

        while (m_running) {
            m_window->onUpdate();
        }
    }
}
