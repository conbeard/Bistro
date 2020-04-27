//
// Created by Connor Beard on 4/26/20.
//

#ifndef BISTRO_OPENGLRENDERERAPI_H
#define BISTRO_OPENGLRENDERERAPI_H

#include "Bistro/Renderer/RendererAPI.h"

namespace Bistro {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        void setClearColor(const glm::vec4& color) override;
        void clear() override;

        void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };
}

#endif //BISTRO_OPENGLRENDERERAPI_H