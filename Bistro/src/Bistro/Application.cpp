//
// Created by Connor Beard on 4/20/20.
//
#include "bpch.h"
#include "Application.h"

#include "Events/MouseEvent.h"
#include "Log.h"

namespace Bistro {
    Application::Application() = default;

    Application::~Application() = default;

    void Application::Run() {
        MouseMovedEvent e(720, 360);
        B_LOGGER_TRACE(e);

        B_LOGGER_INFO("Running...");
        while (true) {
            char input = '\0';
            std::cin >> input;
            if (input == 'q') break;
        }
        B_LOGGER_CRITICAL("Finishing...");
    }
}
