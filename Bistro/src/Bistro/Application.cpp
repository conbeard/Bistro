//
// Created by Connor Beard on 4/20/20.
//

#include <iostream>
#include "Application.h"

namespace Bistro {
    Application::Application() = default;

    Application::~Application() = default;

    void Application::Run() {
        std::cout << "Running...\n";
        while (true) {
            char input = '\0';
            std::cin >> input;
            if (input == 'q') break;
        }
        std::cout << "Finishing...\n";
    }
}
