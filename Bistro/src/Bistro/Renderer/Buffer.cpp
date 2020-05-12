//
// Created by Connor Beard on 4/25/20.
//

#include "bpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Bistro/Core/Core.h"
#include "Bistro/Core/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Bistro {

    Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size) {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::API::None is not supported");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLVertexBuffer>(vertices, size);
            default:
                B_CORE_ASSERT(false, "Unknown RendererAPI");
                return nullptr;
        }
    }

    Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t count) {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
            B_CORE_ASSERT(false, "RendererAPI::API::None is not supported");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLIndexBuffer>(indices, count);
            default:
            B_CORE_ASSERT(false, "Unknown RendererAPI");
                return nullptr;
        }
    }
}
