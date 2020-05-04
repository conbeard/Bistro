//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_RENDERER_H
#define BISTRO_RENDERER_H

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Bistro {

    class Renderer {
    public:
        static void beginScene(OrthographicCamera& camera);
        static void endScene();

        static void submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    public:
        struct SceneData {
            glm::mat4 viewProjectMatrix;
        };

        static SceneData* s_sceneData;
    };
}

#endif //BISTRO_RENDERER_H
