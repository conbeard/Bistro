//
// Created by Connor Beard on 4/20/20.
//
#include "bpch.h"
#include "Application.h"
#include "Log.h"
#include "Core.h"
#include "Bistro/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Bistro {

    Application* Application::s_instance = nullptr;

    Application::Application() {
        B_CORE_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;

        m_window = Scope<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

        Renderer::init();

        m_imguiLayer = new ImGuiLayer();
        pushOverlay(m_imguiLayer);
    }

    Application::~Application() {
        Renderer::shutdown();
    };

    void Application::Run() {
        while (m_running) {
            auto time = (float) glfwGetTime(); // Temporary, replace with platform specific
            Timestep timestep = time - m_lastFrameTime;
            m_lastFrameTime = time;

            if (!m_minimized) {
                for (Layer *layer : m_layerStack)
                    layer->onUpdate(timestep);
            }

            // Render ImGui
            m_imguiLayer->begin();
            for (Layer *layer : m_layerStack)
                layer->onImGuiRender();
            m_imguiLayer->end();

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event &e) {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::onWindowResize));

        for (auto it = m_layerStack.end(); it != m_layerStack.begin(); ) {
            (*--it)->onEvent(e);
            if (e.handled) break;
        }
    }

    void Application::pushLayer(Layer *layer) {
        m_layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer *overlay) {
        m_layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    bool Application::onWindowClose(WindowCloseEvent& event) {
        m_running = false;
        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent& event) {
        if (event.getWidth() == 0 || event.getHeight() == 0) {
            m_minimized = true;
            return false;
        }
        Renderer::onWindowResize(event.getWidth(), event.getHeight());
        m_minimized = false;
        return false;
    }
}
