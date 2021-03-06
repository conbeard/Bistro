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
        Ref<Shader> textureShader;
        Ref<Texture2D> whiteTexture;
    };

    static Renderer2DStorage* s_data;

    void Renderer2D::init() {
        s_data = new Renderer2DStorage();
        s_data->quadVertexArray = Bistro::VertexArray::create();

        float rectVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        Ref<VertexBuffer> squareVB;
        Ref<IndexBuffer> squareIB;

        squareVB = VertexBuffer::create(rectVertices, sizeof(rectVertices));
        BufferLayout layout = {
                { ShaderDataType::Float3, "a_position" },
                { ShaderDataType::Float2, "a_textCoord" }
        };
        squareVB->setLayout(layout);
        s_data->quadVertexArray->addVertexBuffer(squareVB);

        uint32_t rectIndices[6] = { 0, 1, 2, 2, 3, 0 };
        squareIB = IndexBuffer::create(rectIndices, 6);
        s_data->quadVertexArray->setIndexBuffer(squareIB);

        s_data->whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data->whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

        s_data->textureShader = Shader::create("assets/shaders/texture.glsl");
        s_data->textureShader->bind();
        s_data->textureShader->setInt("u_texture", 0);
    }

    void Renderer2D::shutdown() {
        delete s_data; s_data = nullptr;
    }

    void Renderer2D::beginScene(OrthographicCamera &camera) {
        s_data->textureShader->bind();
        s_data->textureShader->setMat4("u_viewProjection", camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene() {

    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        drawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_data->textureShader->setMat4("u_transform", transform);
        s_data->textureShader->setFloat4("u_color", color);
        s_data->whiteTexture->bind();
        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture) {
        drawQuad({position.x, position.y, 0.0f}, size, texture);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_data->textureShader->setMat4("u_transform", transform);
        s_data->textureShader->setFloat4("u_color", glm::vec4(1.0f));
        texture->bind();
        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }
}
