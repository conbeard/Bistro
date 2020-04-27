//
// Created by Connor Beard on 4/26/20.
//

#include "bpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Bistro {

    VertexArray *VertexArray::create() {
        switch (Renderer::getAPI()) {
            case RendererAPI::None: B_CORE_ASSERT(false, "RendererAPI::None is not supported");
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexArray();
            default: B_CORE_ASSERT(false, "Unknown RendererAPI");
                return nullptr;
        }
    }
}
