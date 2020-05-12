//
// Created by Connor Beard on 5/11/20.
//

#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Bistro::Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f) {}

void Sandbox2D::onAttach() {

    float rectVertices[3 * 4] = {
            -0.5f,  -0.5f,  0.0f,
            0.5f,   -0.5f,  0.0f,
            0.5f,   0.5f,  0.0f,
            -0.5f,  0.5f,  0.0f
    };

    Bistro::Ref<Bistro::VertexBuffer> squareVB;
    Bistro::Ref<Bistro::IndexBuffer> squareIB;

    m_vertexArray = Bistro::VertexArray::create();
    squareVB = Bistro::VertexBuffer::create(rectVertices, sizeof(rectVertices));
    Bistro::BufferLayout layout = {
            { Bistro::ShaderDataType::Float3, "a_position" }
    };
    squareVB->setLayout(layout);
    m_vertexArray->addVertexBuffer(squareVB);

    uint32_t rectIndices[6] = { 0, 1, 2, 2, 3, 0 };
    squareIB = Bistro::IndexBuffer::create(rectIndices, 6);
    m_vertexArray->setIndexBuffer(squareIB);

    m_flatColorShader = Bistro::Shader::create("assets/shaders/flatColor.glsl");
}

void Sandbox2D::onDetach() {

}

void Sandbox2D::onUpdate(Bistro::Timestep ts) {
    // Update
    m_cameraController.onUpdate(ts);

    // Render
    Bistro::RenderCommand::setClearColor({0.4, 1, 1, 1});
    Bistro::RenderCommand::clear();
    Bistro::Renderer::beginScene(m_cameraController.getCamera());

    m_flatColorShader->bind();
    m_flatColorShader->uploadUniformFloat4("u_color", m_rectColor);

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            glm::vec3 pos = {j * 0.11f, i * 0.11f, 0.0f};
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
                    glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
            Bistro::Renderer::submit(m_flatColorShader, m_vertexArray, transform);
        }
    }

    Bistro::Renderer::endScene();
}

void Sandbox2D::onImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Rect color", glm::value_ptr(m_rectColor));
    ImGui::End();
}

void Sandbox2D::onEvent(Bistro::Event &event) {
    m_cameraController.onEvent(event);
}
