//
// Created by Connor Beard on 4/25/20.
//

#include "bpch.h"
#include "Shader.h"

#include "Bistro/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Bistro {
    Shader *Shader::create(const std::string &vertexFilename, const std::string &fragmentFilename) {
        switch (Renderer::getAPI()) {
            default:
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is not supported!")
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexFilename, fragmentFilename);
        }
    }
}
