//
// Created by Connor Beard on 4/26/20.
//

#include "bpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/MacOS/MacVertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Bistro {

    VertexArray *VertexArray::create() {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None: B_CORE_ASSERT(false, "RendererAPI::API::None is not supported");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new MacVertexArray();
            default: B_CORE_ASSERT(false, "Unknown RendererAPI");
                return nullptr;
        }
    }
}
