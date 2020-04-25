//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_APPLICATION_H
#define BISTRO_APPLICATION_H

#include "bpch.h"
#include "Core.h"

#include "Window.h"
#include "Input.h"
#include "Layer.h"
#include "Bistro/ImGui/ImGuiLayer.h"
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

        static inline Application& get() { return *s_instance; }
        inline Window& getWindow() { return *m_window; }
    private:
        bool onWindowClose(WindowCloseEvent);

        std::unique_ptr<Window> m_window;
        ImGuiLayer* m_imguiLayer;
        bool m_running = true;
        LayerStack m_layerStack;

        unsigned int m_vertexArray, m_vertexBuffer, m_indexBuffer;

        static Application* s_instance;
    };

    // To be implemented in client
    Application* CreateApplication();
}

#endif //BISTRO_APPLICATION_H
