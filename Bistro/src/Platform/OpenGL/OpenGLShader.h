//
// Created by Connor Beard on 5/4/20.
//

#ifndef BISTRO_OPENGLSHADER_H
#define BISTRO_OPENGLSHADER_H

#include "Bistro/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Bistro {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexFilename, const std::string& fragmentFilename);
        virtual ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        void uploadUniformInt(const std::string &name, int value) const;

        void uploadUniformFloat(const std::string &name, float values) const;
        void uploadUniformFloat2(const std::string &name, const glm::vec2 &values) const;
        void uploadUniformFloat3(const std::string &name, const glm::vec3 &values) const;
        void uploadUniformFloat4(const std::string &name, const glm::vec4 &values) const;

        void uploadUniformMat3(const std::string &name, const glm::mat3 &matrix) const;
        void uploadUniformMat4(const std::string &name, const glm::mat4 &matrix) const;
    private:
        uint32_t m_rendererID;
    };
}


#endif //BISTRO_OPENGLSHADER_H
