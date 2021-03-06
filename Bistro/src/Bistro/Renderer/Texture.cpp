//
// Created by Connor Beard on 5/6/20.
//

#include "bpch.h"
#include "Texture.h"

#include "Bistro/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Bistro {
    Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height) {
        switch (Renderer::getAPI()) {
            default:
            case RendererAPI::API::None:
            B_CORE_ASSERT(false, "RendererAPI::API::None is not supported");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return createRef<OpenGLTexture2D>(width, height);
        }
    }

    Ref<Texture2D> Texture2D::create(const std::string &path) {
        switch (Renderer::getAPI()) {
            default:
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::API::None is not supported");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return createRef<OpenGLTexture2D>(path);
        }
    }
}
