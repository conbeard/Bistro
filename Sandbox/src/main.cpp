//
// Created by Connor Beard on 4/20/20.
//

#include <Bistro.h>
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

class ExampleLayer : public Bistro::Layer {
public:
    ExampleLayer() : Layer("Example"), m_cameraController(1280.0f / 720.0f) {

        float rectVertices[5 * 4] = {
                -0.5f,  -0.5f,  0.0f, 0.0f, 0.0f,
                0.5f,   -0.5f,  0.0f, 1.0f, 0.0f,
                0.5f,   0.5f,  0.0f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.0f,  0.0f, 1.0f
        };

        Bistro::Ref<Bistro::VertexBuffer> squareVB;
        Bistro::Ref<Bistro::IndexBuffer> squareIB;

        m_squareVertexArray.reset(Bistro::VertexArray::create());
        squareVB.reset(Bistro::VertexBuffer::create(rectVertices, sizeof(rectVertices)));
        Bistro::BufferLayout layout = {
                { Bistro::ShaderDataType::Float3, "a_position" },
                { Bistro::ShaderDataType::Float2, "a_texCoord" },
        };
        squareVB->setLayout(layout);
        m_squareVertexArray->addVertexBuffer(squareVB);

        uint32_t rectIndices[6] = { 0, 1, 2, 2, 3, 0 };
        squareIB.reset(Bistro::IndexBuffer::create(rectIndices, 6));
        m_squareVertexArray->setIndexBuffer(squareIB);

        m_shaderLibrary.load("assets/shaders/vertexColor.glsl");
        m_shaderLibrary.load("assets/shaders/texture.glsl");

        m_cupheadTexture = Bistro::Texture2D::create("assets/textures/Cuphead.png");
        m_shaderLibrary.get("texture")->bind();
        std::dynamic_pointer_cast<Bistro::OpenGLShader>(m_shaderLibrary.get("texture"))->
                uploadUniformInt("u_texture", 0);
    }

    void onUpdate(Bistro::Timestep ts) override {
        B_TRACE("FPS: {0}, Delta time: {1}ms", 1.0f / ts.getSeconds(), ts.getMilliseconds());
        Bistro::RenderCommand::setClearColor({0.4, 1, 1, 1});
        Bistro::RenderCommand::clear();
        Bistro::Renderer::beginScene(m_cameraController.getCamera());

        m_cameraController.onUpdate(ts);

        m_shaderLibrary.get("vertexColor")->bind();
        std::dynamic_pointer_cast<Bistro::OpenGLShader>(m_shaderLibrary.get("vertexColor"))->
                uploadUniformFloat4("u_color", m_rectColor);

        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                glm::vec3 pos = {j * 0.11f, i * 0.11f, 0.0f};
                glm::mat4 t = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
                Bistro::Renderer::submit(m_shaderLibrary.get("vertexColor"), m_squareVertexArray, t);
            }
        }

        // Textured rect
        m_cupheadTexture->bind();
        Bistro::Renderer::submit(m_shaderLibrary.get("texture"), m_squareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

        Bistro::Renderer::endScene();
    }

    void onEvent(Bistro::Event& e) override {
        m_cameraController.onEvent(e);

    }

    void onImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Rect color", glm::value_ptr(m_rectColor));
        ImGui::End();
    }

private:
    Bistro::ShaderLibrary m_shaderLibrary;
    Bistro::Ref<Bistro::VertexArray> m_squareVertexArray;

    Bistro::Ref<Bistro::Texture2D> m_cupheadTexture;

    Bistro::OrthographicCameraController m_cameraController;

    glm::vec4 m_rectColor = {0.2f, 0.3f, 0.8f, 1.0f};
};

class Sandbox : public Bistro::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
    }

    ~Sandbox() override {
        B_INFO("Sandbox Destructor!");
    }
};

Bistro::Application* Bistro::CreateApplication() {
    return new Sandbox();
}
