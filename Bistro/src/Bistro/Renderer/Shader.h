//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_SHADER_H
#define BISTRO_SHADER_H

namespace Bistro {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static Shader* create(const std::string& vertexSrc, const std::string& fragmentSrc);
        static Shader* create(const std::string& filepath);
    };
}

#endif //BISTRO_SHADER_H
