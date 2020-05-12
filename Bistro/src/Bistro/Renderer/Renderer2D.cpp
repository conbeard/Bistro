//
// Created by Connor Beard on 5/12/20.
//

#include "bpch.h"
#include "Renderer2D.h"

#include "Bistro/Renderer/VertexArray.h"
#include "Bistro/Renderer/Shader.h"
#include "Bistro/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Bistro {

    struct Renderer2DStorage {
        Ref<VertexArray> quadVertexArray;
        Ref<Shader> flatColorShader;
    };

    static Renderer2DStorage* s_data;

    void Renderer2D::init() {
        s_data = new Renderer2DStorage();
        s_data->quadVertexArray = Bistro::VertexArray::create();

        float rectVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        Ref<VertexBuffer> squareVB;
        Ref<IndexBuffer> squareIB;

        squareVB = VertexBuffer::create(rectVertices, sizeof(rectVertices));
        BufferLayout layout = {
                { ShaderDataType::Float3, "a_position" }
        };
        squareVB->setLayout(layout);
        s_data->quadVertexArray->addVertexBuffer(squareVB);

        uint32_t rectIndices[6] = { 0, 1, 2, 2, 3, 0 };
        squareIB = IndexBuffer::create(rectIndices, 6);
        s_data->quadVertexArray->setIndexBuffer(squareIB);

        s_data->flatColorShader = Shader::create("assets/shaders/flatColor.glsl");
    }

    void Renderer2D::shutdown() {
        delete s_data; s_data = nullptr;
    }

    void Renderer2D::beginScene(OrthographicCamera &camera) {
        s_data->flatColorShader->bind();
        s_data->flatColorShader->uploadUniformMat4("u_viewProjection", camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene() {

    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        drawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_data->flatColorShader->bind();
        s_data->flatColorShader->uploadUniformFloat4("u_color", color);
        s_data->flatColorShader->uploadUniformMat4("u_transform", transform);
        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }
}
