//
// Created by Connor Beard on 5/11/20.
//

#ifndef BISTRO_SANDBOX2D_H
#define BISTRO_SANDBOX2D_H

#include <Bistro.h>

class Sandbox2D : public Bistro::Layer {
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(Bistro::Timestep ts) override;
    void onImGuiRender() override;
    void onEvent(Bistro::Event& event) override;

private:
    Bistro::Ref<Bistro::Shader> m_flatColorShader;
    Bistro::Ref<Bistro::Texture2D> m_texture;
    Bistro::Ref<Bistro::VertexArray> m_vertexArray;
    Bistro::OrthographicCameraController m_cameraController;

    glm::vec4 m_rectColor = {0.2f, 0.3f, 0.8f, 1.0f};
};

#endif //BISTRO_SANDBOX2D_H
