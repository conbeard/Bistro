//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_RENDERER_H
#define BISTRO_RENDERER_H

namespace Bistro {

    enum class RendererAPI {
        None = 0,
        OpenGL = 1,
    };

    class Renderer {
    public:
        inline static RendererAPI getAPI() { return s_rendererAPI; }
    private:
        static RendererAPI s_rendererAPI;
    };
}

#endif //BISTRO_RENDERER_H
