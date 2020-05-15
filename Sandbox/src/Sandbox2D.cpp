//
// Created by Connor Beard on 5/11/20.
//

#include "Sandbox2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

template<typename Fn>
class Timer {
public:
    Timer(const char* name, Fn&& func) : m_name(name), m_func(func), m_stopped(false) {
        m_startTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        if (!m_stopped) stop();
    }

    void stop() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        m_stopped = true;
        float duration = (end - start) * 0.001f;

        m_func({m_name, duration});
    }

private:
    const char* m_name;
    Fn m_func;
    std::chrono::time_point<std::chrono::steady_clock> m_startTimepoint;
    bool m_stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_profileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D() : Bistro::Layer("Sandbox2D"), m_cameraController(1280.0f / 720.0f) {}

void Sandbox2D::onAttach() {
    m_texture = Bistro::Texture2D::create("assets/textures/Cuphead.png");
}

void Sandbox2D::onDetach() {
    Bistro::Renderer2D::shutdown();
}

void Sandbox2D::onUpdate(Bistro::Timestep ts) {
    PROFILE_SCOPE("Sandbox2D::onUpdate");

    // Update
    {
        PROFILE_SCOPE("CameraController::onUpdate");
        m_cameraController.onUpdate(ts);
    }

    // Render
    {
        PROFILE_SCOPE("Set Clear Color");
        Bistro::RenderCommand::setClearColor({0.4, 1, 1, 1});
        Bistro::RenderCommand::clear();
    }

    {
        PROFILE_SCOPE("Draw scene");
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
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Rect color", glm::value_ptr(m_rectColor));

    for (auto& result : m_profileResults) {
        char label[50];
        strcpy(label, "%.3fms ");
        strcat(label, result.name);

        ImGui::Text(label, result.time);
    }
    m_profileResults.clear();

    ImGui::End();
}

void Sandbox2D::onEvent(Bistro::Event &event) {
    m_cameraController.onEvent(event);
}
