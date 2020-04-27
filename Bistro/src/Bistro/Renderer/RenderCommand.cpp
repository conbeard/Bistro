//
// Created by Connor Beard on 4/26/20.
//

#include "bpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Bistro {
    RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI();
}
