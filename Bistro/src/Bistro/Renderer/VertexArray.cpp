//
// Created by Connor Beard on 4/26/20.
//

#include "bpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Bistro {

    Ref<VertexArray> VertexArray::create() {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None: B_CORE_ASSERT(false, "RendererAPI::API::None is not supported");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLVertexArray>();
            default: B_CORE_ASSERT(false, "Unknown RendererAPI");
                return nullptr;
        }
    }
}
