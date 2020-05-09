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
    ExampleLayer() : Layer("Example"), m_camera(-1.28f, 1.28f, -0.72f, 0.72f), m_cameraPosition(0.0f), m_trianglePosition(0.0f) {

//        m_vertexArray.reset(Bistro::VertexArray::create());
//
//        float vertices[3 * 3] = {
//                -0.5f,  -0.5f,  0.0f,
//                0.0f,  -0.5f,  0.0f,
//                -0.25f,  0.5f,  0.0f
//        };
//
//        Bistro::Ref<Bistro::VertexBuffer> triangleVB;
//        Bistro::Ref<Bistro::IndexBuffer> triangleIB;
//
//        triangleVB.reset(Bistro::VertexBuffer::create(vertices, sizeof(vertices)));
//        Bistro::BufferLayout layout = {
//                { Bistro::ShaderDataType::Float3, "a_position" },
//        };
//        triangleVB->setLayout(layout);
//        m_vertexArray->addVertexBuffer(triangleVB);
//
//        uint32_t indices[3] = { 0, 1, 2 };
//        triangleIB.reset(Bistro::IndexBuffer::create(indices, 3));
//        m_vertexArray->setIndexBuffer(triangleIB);


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

        // WASD QE Camera controls
        if (Bistro::Input::isKeyPressed(B_KEY_A))
            m_cameraPosition.x -= m_cameraSpeed * ts;
        if (Bistro::Input::isKeyPressed(B_KEY_D))
            m_cameraPosition.x += m_cameraSpeed * ts;
        if (Bistro::Input::isKeyPressed(B_KEY_S))
            m_cameraPosition.y -= m_cameraSpeed * ts;
        if (Bistro::Input::isKeyPressed(B_KEY_W))
            m_cameraPosition.y += m_cameraSpeed * ts;
        if (Bistro::Input::isKeyPressed(B_KEY_Q))
            m_cameraRotation += m_cameraSpeed * ts;
        if (Bistro::Input::isKeyPressed(B_KEY_E))
            m_cameraRotation -= m_cameraSpeed * ts;

        // TFGH triangle controls
        if (Bistro::Input::isKeyPressed(B_KEY_H))
            m_trianglePosition.x += m_cameraSpeed * ts;
        if (Bistro::Input::isKeyPressed(B_KEY_F))
            m_trianglePosition.x -= m_cameraSpeed * ts;
        if (Bistro::Input::isKeyPressed(B_KEY_T))
            m_trianglePosition.y += m_cameraSpeed * ts;
        if (Bistro::Input::isKeyPressed(B_KEY_G))
            m_trianglePosition.y -= m_cameraSpeed * ts;

        m_camera.setPosition(m_cameraPosition);
        m_camera.setRotation(m_cameraRotation);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_trianglePosition);

        Bistro::Renderer::beginScene(m_camera);

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

        // Triangle
//        Bistro::Renderer::submit(m_shader, m_vertexArray, transform);

        Bistro::Renderer::endScene();
    }

    void onEvent(Bistro::Event& e) override {
        Bistro::EventDispatcher dispatcher(e);
        dispatcher.dispatch<Bistro::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::onKeyPressed));

    }

    void onImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Rect color", glm::value_ptr(m_rectColor));
        ImGui::End();
    }

    bool onKeyPressed(Bistro::KeyPressedEvent& event) {
        return false;
    }

private:
    Bistro::ShaderLibrary m_shaderLibrary;
    Bistro::Ref<Bistro::VertexArray> m_squareVertexArray;

    Bistro::Ref<Bistro::Texture2D> m_cupheadTexture;

    Bistro::OrthographicCamera m_camera;
    glm::vec3 m_cameraPosition;
    float m_cameraRotation = 0.0f;
    float m_cameraSpeed = 2.0f;

    glm::vec3 m_trianglePosition;
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
