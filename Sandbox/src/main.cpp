//
// Created by Connor Beard on 4/20/20.
//

#include <Bistro.h>
#include <imgui.h>

class ExampleLayer : public Bistro::Layer {
public:
    ExampleLayer() : Layer("Example"), m_camera(-1.28f, 1.28f, -0.72f, 0.72f), m_cameraPosition(0.0f) {

        m_vertexArray.reset(Bistro::VertexArray::create());

        float vertices[7 * 3] = {
                -0.5f,  -0.5f,  0.0f, 0.7f, 0.4f, 1.0f, 1.0f,
                0.0f,  -0.5f,  0.0f, 1.0f, 0.4f, 0.4f, 1.0f,
                -0.25f,  0.5f,  0.0f, 0.8f, 1.0f, 0.4f, 1.0f
        };

        std::shared_ptr<Bistro::VertexBuffer> triangleVB;
        std::shared_ptr<Bistro::IndexBuffer> triangleIB;

        triangleVB.reset(Bistro::VertexBuffer::create(vertices, sizeof(vertices)));
        Bistro::BufferLayout layout = {
                { Bistro::ShaderDataType::Float3, "a_position" },
                { Bistro::ShaderDataType::Float4, "a_color" },
        };
        triangleVB->setLayout(layout);
        m_vertexArray->addVertexBuffer(triangleVB);

        uint32_t indices[3] = { 0, 1, 2 };
        triangleIB.reset(Bistro::IndexBuffer::create(indices, 3));
        m_vertexArray->setIndexBuffer(triangleIB);


        float rectVertices[7 * 4] = {
                0.0f,  -0.5f,  0.0f, 1.0f, 0.4f, 0.4f, 1.0f,
                0.0f,   0.5f,  0.0f, 0.8f, 1.0f, 0.4f, 1.0f,
                1.0f,   0.5f,  0.0f, 1.0f, 0.4f, 0.4f, 1.0f,
                1.0f,  -0.5f,  0.0f, 0.7f, 0.4f, 1.0f, 1.0f
        };

        std::shared_ptr<Bistro::VertexBuffer> squareVB;
        std::shared_ptr<Bistro::IndexBuffer> squareIB;

        m_squareVertexArray.reset(Bistro::VertexArray::create());
        squareVB.reset(Bistro::VertexBuffer::create(rectVertices, sizeof(rectVertices)));
        squareVB->setLayout(layout);
        m_squareVertexArray->addVertexBuffer(squareVB);

        uint32_t rectIndices[6] = { 0, 1, 2, 2, 3, 0 };
        squareIB.reset(Bistro::IndexBuffer::create(rectIndices, 6));
        m_squareVertexArray->setIndexBuffer(squareIB);

        // TODO: add shader files to the build process to automatically move them
        m_shader = std::make_unique<Bistro::Shader>("Shaders/vertex.glsl", "Shaders/fragment.glsl");
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

        m_camera.setPosition(m_cameraPosition);
        m_camera.setRotation(m_cameraRotation);

        Bistro::Renderer::beginScene(m_camera);
        Bistro::Renderer::submit(m_shader, m_vertexArray);
        Bistro::Renderer::submit(m_shader, m_squareVertexArray);
        Bistro::Renderer::endScene();
    }

    void onEvent(Bistro::Event& e) override {
        Bistro::EventDispatcher dispatcher(e);
        dispatcher.dispatch<Bistro::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::onKeyPressed));

    }

    void onImGuiRender() override {

    }

    bool onKeyPressed(Bistro::KeyPressedEvent& event) {
        return false;
    }

private:
    std::shared_ptr<Bistro::Shader> m_shader;
    std::shared_ptr<Bistro::VertexArray> m_vertexArray;
    std::shared_ptr<Bistro::VertexArray> m_squareVertexArray;

    Bistro::OrthographicCamera m_camera;
    glm::vec3 m_cameraPosition;
    float m_cameraRotation = 0.0f;
    float m_cameraSpeed = 2.0f;
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
