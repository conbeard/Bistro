//
// Created by Connor Beard on 4/25/20.
//

#include "bpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Bistro {

    Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

    void Renderer::init() {
        RenderCommand::init();
    }

    void Renderer::onWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::setViewport(0, 0, width, height);
    }

    void Renderer::beginScene(OrthographicCamera& camera) {
        s_sceneData->viewProjectMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene() {

    }

    void Renderer::submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4& transform) {
        shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_viewProjection", s_sceneData->viewProjectMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
