//
// Created by Connor Beard on 4/20/20.
//
#include "bpch.h"
#include "Application.h"
#include "Log.h"

#include <glad/glad.h>

namespace Bistro {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() {
        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_layerStack)
                layer->onUpdate();

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event &e) {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        B_CORE_TRACE("{0}", e);

        for (auto it = m_layerStack.end(); it != m_layerStack.begin(); ) {
            (*--it)->onEvent(e);
            if (e.handled) break;
        }
    }

    void Application::pushLayer(Layer *layer) {
        m_layerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer *overlay) {
        m_layerStack.pushOverlay(overlay);
    }

    bool Application::onWindowClose(WindowCloseEvent) {
        m_running = false;
        return true;
    }
}
