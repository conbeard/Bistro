//
// Created by Connor Beard on 4/26/20.
//

#ifndef BISTRO_RENDERERAPI_H
#define BISTRO_RENDERERAPI_H

#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Bistro {

    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL = 1,
        };
    public:
        virtual void init() = 0;

        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void clear() = 0;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        inline static API getAPI() { return s_API; }
    private:
        static API s_API;
    };
}

#endif //BISTRO_RENDERERAPI_H
