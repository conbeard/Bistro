//
// Created by Connor Beard on 5/11/20.
//

#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Bistro::Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f) {}

void Sandbox2D::onAttach() {
    m_texture = Bistro::Texture2D::create("assets/textures/Cuphead.png");
}

void Sandbox2D::onDetach() {
    Bistro::Renderer2D::shutdown();
}

void Sandbox2D::onUpdate(Bistro::Timestep ts) {
    B_PROFILE_FUNCTION();

    // Update
    {
        B_PROFILE_SCOPE("CameraController::onUpdate");
        m_cameraController.onUpdate(ts);
    }

    // Render
    {
        B_PROFILE_SCOPE("Set Clear Color");
        Bistro::RenderCommand::setClearColor({0.4, 1, 1, 1});
        Bistro::RenderCommand::clear();
    }

    {
        B_PROFILE_SCOPE("Draw scene");
        Bistro::Renderer2D::beginScene(m_cameraController.getCamera());
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                glm::vec3 pos = {j * 0.11f, i * 0.11f, 0.0f};
                Bistro::Renderer2D::drawQuad(pos, {0.1f, 0.1f}, m_rectColor);
            }
        }
        Bistro::Renderer2D::drawQuad({1.05f, 1.05f, 0.1f}, {2.2f, 2.2f}, m_texture);
        Bistro::Renderer2D::endScene();
    }
}

void Sandbox2D::onImGuiRender() {
    B_PROFILE_FUNCTION();
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Rect color", glm::value_ptr(m_rectColor));
    ImGui::End();
}

void Sandbox2D::onEvent(Bistro::Event &event) {
    B_PROFILE_FUNCTION();
    m_cameraController.onEvent(event);
}
