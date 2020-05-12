//
// Created by Connor Beard on 4/25/20.
//

#include "bpch.h"
#include "Renderer.h"

#include "Bistro/Renderer/Renderer2D.h"
#include "Bistro/Renderer/RenderCommand.h"

namespace Bistro {

    Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

    void Renderer::init() {
        RenderCommand::init();
        Renderer2D::init();
    }

    void Renderer::shutdown() {
        Renderer2D::shutdown();
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
        shader->setMat4("u_viewProjection", s_sceneData->viewProjectMatrix);
        shader->setMat4("u_transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
