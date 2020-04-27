//
// Created by Connor Beard on 4/20/20.
//
#include "bpch.h"
#include "Application.h"
#include "Log.h"
#include "Core.h"
#include "Bistro/Renderer/Buffer.h"

#include <glad/glad.h>

#include <memory>

namespace Bistro {

    Application* Application::s_instance = nullptr;

    Application::Application() {
        B_CORE_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

        m_imguiLayer = new ImGuiLayer();
        pushOverlay(m_imguiLayer);

        m_vertexArray.reset(VertexArray::create());

        float vertices[7 * 3] = {
                -0.5f,  -0.5f,  0.0f, 0.7f, 0.4f, 1.0f, 1.0f,
                 0.0f,  -0.5f,  0.0f, 1.0f, 0.4f, 0.4f, 1.0f,
                -0.25f,  0.5f,  0.0f, 0.8f, 1.0f, 0.4f, 1.0f
        };

        m_vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
        BufferLayout layout = {
                { ShaderDataType::Float3, "a_position" },
                { ShaderDataType::Float4, "a_color" },
        };
        m_vertexBuffer->setLayout(layout);
        m_vertexArray->addVertexBuffer(m_vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::create(indices, 3));
        m_vertexArray->setIndexBuffer(m_indexBuffer);


        float rectVertices[7 * 4] = {
                0.0f,  -0.5f,  0.0f, 1.0f, 0.4f, 0.4f, 1.0f,
                0.0f,   0.5f,  0.0f, 0.8f, 1.0f, 0.4f, 1.0f,
                0.5f,   0.5f,  0.0f, 1.0f, 0.4f, 0.4f, 1.0f,
                0.5f,  -0.5f,  0.0f, 0.7f, 0.4f, 1.0f, 1.0f
        };

        m_squareVertexArray.reset(VertexArray::create());
        m_squareVertexBuffer.reset(VertexBuffer::create(rectVertices, sizeof(rectVertices)));
        m_squareVertexBuffer->setLayout(layout);
        m_squareVertexArray->addVertexBuffer(m_squareVertexBuffer);

        uint32_t rectIndices[6] = { 0, 1, 2, 2, 3, 0 };
        m_squareIndexBuffer.reset(IndexBuffer::create(rectIndices, 6));
        m_squareVertexArray->setIndexBuffer(m_squareIndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

            out vec4 v_color;

            void main() {
                v_color = a_color;
                gl_Position = vec4(a_position, 1);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 o_color;

            in vec4 v_color;

            void main() {
                o_color = v_color;
            }
        )";

        m_shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
    }

    Application::~Application() = default;

    void Application::Run() {
        while (m_running) {
            glClearColor(0.4, 1, 1, 1);
//            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->bind();
            m_vertexArray->bind();
            glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

            m_squareVertexArray->bind();
            glDrawElements(GL_TRIANGLES, m_squareIndexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_layerStack)
                layer->onUpdate();

            // Render ImGui
            m_imguiLayer->begin();
            for (Layer* layer : m_layerStack)
                layer->onImGuiRender();
            m_imguiLayer->end();

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
