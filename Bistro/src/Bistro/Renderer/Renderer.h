//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_RENDERER_H
#define BISTRO_RENDERER_H

#include "RenderCommand.h"

namespace Bistro {

    class Renderer {
    public:
        static void beginScene();
        static void endScene();

        static void submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
    };
}

#endif //BISTRO_RENDERER_H
