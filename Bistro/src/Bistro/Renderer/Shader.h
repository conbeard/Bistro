//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_SHADER_H
#define BISTRO_SHADER_H

#include <glm/glm.hpp>

namespace Bistro {

    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;

        void uploadUniformMat4(const std::string &name, const glm::mat4 &matrix);
    private:
        uint32_t m_rendererID;
    };
}

#endif //BISTRO_SHADER_H
