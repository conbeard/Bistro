//
// Created by Connor Beard on 4/25/20.
//

#include "bpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Bistro/Core.h"
#include "Bistro/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Bistro {

    VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size) {
        switch (Renderer::getAPI()) {
            case RendererAPI::None:
                B_CORE_ASSERT(false, "RendererAPI::None is not supported");
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
            default:
                B_CORE_ASSERT(false, "Unknown RendererAPI");
                return nullptr;
        }
    }

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count) {
        switch (Renderer::getAPI()) {
            case RendererAPI::None:
            B_CORE_ASSERT(false, "RendererAPI::None is not supported");
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, count);
            default:
            B_CORE_ASSERT(false, "Unknown RendererAPI");
                return nullptr;
        }
    }
}
