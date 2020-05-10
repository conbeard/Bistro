//
// Created by Connor Beard on 4/26/20.
//

#ifndef BISTRO_OPENGLRENDERERAPI_H
#define BISTRO_OPENGLRENDERERAPI_H

#include "Bistro/Renderer/RendererAPI.h"

namespace Bistro {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        void init() override;
        void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        void setClearColor(const glm::vec4& color) override;
        void clear() override;

        void drawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}

#endif //BISTRO_OPENGLRENDERERAPI_H
