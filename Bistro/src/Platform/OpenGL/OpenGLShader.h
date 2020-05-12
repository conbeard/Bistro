//
// Created by Connor Beard on 5/4/20.
//

#ifndef BISTRO_OPENGLSHADER_H
#define BISTRO_OPENGLSHADER_H

#include "Bistro/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Bistro {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(const std::string& filepath);
        virtual ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        const std::string& getName() const override { return m_name; }

        void setInt(const std::string &name, int value) const override;

        void setFloat(const std::string &name, float values) const override;
        void setFloat2(const std::string &name, const glm::vec2 &values) const override;
        void setFloat3(const std::string &name, const glm::vec3 &values) const override;
        void setFloat4(const std::string &name, const glm::vec4 &values) const override;

        void setMat3(const std::string &name, const glm::mat3 &matrix) const override;
        void setMat4(const std::string &name, const glm::mat4 &matrix) const override;

    private:
        std::string readFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> preprocess(const std::string& shaderSrc);
        void compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);
    private:
        uint32_t m_rendererID;
        std::string m_name;
    };
}


#endif //BISTRO_OPENGLSHADER_H
