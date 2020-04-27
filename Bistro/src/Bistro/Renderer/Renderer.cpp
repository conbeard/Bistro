//
// Created by Connor Beard on 4/25/20.
//

#include "bpch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Bistro {

    void Renderer::beginScene() {

    }

    void Renderer::endScene() {

    }

    void Renderer::submit(const std::shared_ptr<VertexArray> &vertexArray) {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
