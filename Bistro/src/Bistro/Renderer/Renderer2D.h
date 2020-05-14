//
// Created by Connor Beard on 5/12/20.
//

#ifndef BISTRO_RENDERER2D_H
#define BISTRO_RENDERER2D_H

#include "Bistro/Renderer/OrthographicCamera.h"
#include "Bistro/Renderer/Texture.h"

namespace Bistro {

    class Renderer2D {
    public:
        static void init();
        static void shutdown();

        static void beginScene(OrthographicCamera& camera);
        static void endScene();

        // Primitives
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
    };
}

#endif //BISTRO_RENDERER2D_H
