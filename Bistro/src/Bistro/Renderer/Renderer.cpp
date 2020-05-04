//
// Created by Connor Beard on 4/25/20.
//

#include "bpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Bistro {

    Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

    void Renderer::beginScene(OrthographicCamera& camera) {
        s_sceneData->viewProjectMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene() {

    }

    void Renderer::submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4& transform) {
        shader->bind();
        shader->uploadUniformMat4("u_viewProjection", s_sceneData->viewProjectMatrix);
        shader->uploadUniformMat4("u_transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
