//
// Created by Connor Beard on 4/26/20.
//

#ifndef BISTRO_RENDERCOMMAND_H
#define BISTRO_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Bistro {

    class RenderCommand {
    public:
        inline static void init() { s_rendererAPI->init(); }
        inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_rendererAPI->setViewport(x, y, width, height); }

        inline static void setClearColor(const glm::vec4& color) { s_rendererAPI->setClearColor(color); }
        inline static void clear() { s_rendererAPI->clear(); }

        inline static void drawIndexed(const Ref<VertexArray>& vertexArray) {
            s_rendererAPI->drawIndexed(vertexArray);
        }
    private:
        static RendererAPI* s_rendererAPI;
    };

}

#endif //BISTRO_RENDERCOMMAND_H
