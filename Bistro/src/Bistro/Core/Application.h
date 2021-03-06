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
#include "LayerStack.h"
#include "Bistro/Core/Timestep.h"
#include "Bistro/ImGui/ImGuiLayer.h"
#include "Bistro/Events/ApplicationEvent.h"

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
        bool onWindowClose(WindowCloseEvent& event);
        bool onWindowResize(WindowResizeEvent& event);

        Scope<Window> m_window;
        ImGuiLayer* m_imguiLayer;
        bool m_running = true;
        bool m_minimized = false;
        LayerStack m_layerStack;
        float m_lastFrameTime;

        static Application* s_instance;
    };

    // To be implemented in client
    Application* CreateApplication();
}

#endif //BISTRO_APPLICATION_H
