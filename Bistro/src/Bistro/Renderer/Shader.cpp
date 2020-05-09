//
// Created by Connor Beard on 4/25/20.
//

#include "bpch.h"
#include "Shader.h"

#include "Bistro/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Bistro {
    Ref<Shader> Shader::create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (Renderer::getAPI()) {
            default:
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is not supported!")
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }
    }

    Ref<Shader> Shader::create(const std::string &filepath) {
        switch (Renderer::getAPI()) {
            default:
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is not supported!")
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLShader>(filepath);
        }
    }

    void ShaderLibrary::add(const Ref<Shader> &shader) {
        auto name = shader->getName();
        add(name, shader);
    }

    void ShaderLibrary::add(const std::string &name, const Ref<Shader> &shader) {
        B_CORE_ASSERT(m_shaders.find(name) == m_shaders.end(), "Shader already exists");
        m_shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string &filepath) {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string &name, const std::string &filepath) {
        auto shader = Shader::create(filepath);
        add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::get(const std::string &name) {
        B_CORE_ASSERT(m_shaders.find(name) != m_shaders.end(), "Shader does not exist");
        return m_shaders[name];
    }
}
