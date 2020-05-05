//
// Created by Connor Beard on 4/26/20.
//

#ifndef BISTRO_RENDERCOMMAND_H
#define BISTRO_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Bistro {

    class RenderCommand {
    public:
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
