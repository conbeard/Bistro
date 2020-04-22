//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_APPLICATION_H
#define BISTRO_APPLICATION_H

#include "bpch.h"
#include "Core.h"

#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

namespace Bistro {
    class Application {
    public:
        Application();
        virtual ~Application();
        void Run();

        void onEvent(Event& e);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
    private:
        bool onWindowClose(WindowCloseEvent);

        std::unique_ptr<Window> m_window;
        bool m_running = true;
        LayerStack m_layerStack;
    };

    // To be implemented in client
    Application* CreateApplication();
}

#endif //BISTRO_APPLICATION_H
