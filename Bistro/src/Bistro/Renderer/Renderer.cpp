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

    void Renderer::submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray) {
        shader->bind();
        shader->uploadUniformMat4("u_viewProjection", s_sceneData->viewProjectMatrix);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
