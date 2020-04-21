//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_APPLICATION_H
#define BISTRO_APPLICATION_H

#include "bpch.h"
#include "Core.h"
#include "Window.h"

namespace Bistro {
    class Application {
        public:
            Application();
            virtual ~Application();
            void Run();

    private:
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    // To be implemented in client
    Application* CreateApplication();
}

#endif //BISTRO_APPLICATION_H
