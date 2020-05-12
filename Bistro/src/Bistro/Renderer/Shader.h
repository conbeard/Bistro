//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_SHADER_H
#define BISTRO_SHADER_H

#include "Bistro/Core/Core.h"

#include <glm/glm.hpp>

namespace Bistro {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const std::string& getName() const = 0;

        virtual void setInt(const std::string &name, int value) const = 0;

        virtual void setFloat(const std::string &name, float values) const = 0;
        virtual void setFloat2(const std::string &name, const glm::vec2 &values) const = 0;
        virtual void setFloat3(const std::string &name, const glm::vec3 &values) const = 0;
        virtual void setFloat4(const std::string &name, const glm::vec4 &values) const = 0;

        virtual void setMat3(const std::string &name, const glm::mat3 &matrix) const = 0;
        virtual void setMat4(const std::string &name, const glm::mat4 &matrix) const = 0;

        static Ref<Shader> create(const std::string& filepath);
        static Ref<Shader> create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    class ShaderLibrary {
    public:
        void add(const Ref<Shader>& shader);
        void add(const std::string& name, const Ref<Shader>& shader);
        Ref<Shader> load(const std::string& filepath);
        Ref<Shader> load(const std::string& name, const std::string& filepath);

        Ref<Shader> get(const std::string& name);
    private:
        std::unordered_map<std::string, Ref<Shader>> m_shaders;
    };
}

#endif //BISTRO_SHADER_H
