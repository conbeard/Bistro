//
// Created by Connor Beard on 4/20/20.
//
#include "bpch.h"
#include "Application.h"
#include "Log.h"
#include "Core.h"

#include <glad/glad.h>

namespace Bistro {

    Application* Application::s_instance = nullptr;

    Application::Application() {
        B_CORE_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_running) {
            glClearColor(0.4, 1, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_layerStack)
                layer->onUpdate();

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event &e) {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

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

    bool Application::onWindowClose(WindowCloseEvent) {
        m_running = false;
        return true;
    }
}
