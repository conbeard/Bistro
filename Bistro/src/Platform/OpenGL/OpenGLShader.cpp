//
// Created by Connor Beard on 5/4/20.
//

#include "bpch.h"
#include "OpenGLShader.h"

#include "Bistro/Core/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Bistro {

    static GLenum shaderTypeFromString(const std::string& type) {
        if (type == "vertex") return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
        B_CORE_ASSERT(false, "Unknown shader type");
        return GL_FALSE;
    }

    OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) : m_name(name) {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(sources);
    }

    OpenGLShader::OpenGLShader(const std::string &filepath) {
        std::string shaderSrc = readFile(filepath);
        auto sources = preprocess(shaderSrc);
        compile(sources);

        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        lastDot = lastDot == std::string::npos ? filepath.size() : lastDot;
        m_name = filepath.substr(lastSlash, lastDot - lastSlash);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_rendererID);
    }

    void OpenGLShader::bind() const {
        glUseProgram(m_rendererID);
    }

    void OpenGLShader::unbind() const {
        glUseProgram(0);
    }

    void OpenGLShader::setInt(const std::string &name, int value) const {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::setFloat(const std::string &name, float value) const {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::setFloat2(const std::string &name, const glm::vec2 &values) const {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform2f(location, values.x, values.y);
    }

    void OpenGLShader::setFloat3(const std::string &name, const glm::vec3 &values) const {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform3f(location, values.x, values.y, values.z);
    }

    void OpenGLShader::setFloat4(const std::string &name, const glm::vec4 &values) const {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform4f(location, values.x, values.y, values.z, values.w);
    }

    void OpenGLShader::setMat3(const std::string &name, const glm::mat3 &matrix) const {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::setMat4(const std::string &name, const glm::mat4 &matrix) const {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    std::string OpenGLShader::readFile(const std::string &filepath) {
        std::string result;
        std::ifstream file(filepath, std::ios::in | std::ios::binary);
        if (file) {
            file.seekg(0, std::ios::end);
            result.resize(file.tellg());
            file.seekg(0, std::ios::beg);
            file.read(&result[0], result.size());
            file.close();
        } else {
            B_CORE_ERROR("Could not open shader file: {0}", filepath);
        }
        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::preprocess(const std::string &shaderSrc) {
        std::unordered_map<GLenum, std::string> sources;

        const char* typeToken = "#type";
        size_t typeTokenLength = 5;
        size_t pos = shaderSrc.find(typeToken, 0);
        while (pos != std::string::npos) {

            size_t eol = shaderSrc.find_first_of("\n", pos);
            B_CORE_ASSERT((eol != std::string::npos), "Shader Syntax Error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = shaderSrc.substr(begin, eol - begin);
            B_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Invalid Shader Type!");

            size_t nextLinePos = shaderSrc.find_first_not_of("\n", eol);
            pos = shaderSrc.find(typeToken, nextLinePos);
            sources[shaderTypeFromString(type)] =shaderSrc.substr(nextLinePos,
                            pos - (nextLinePos == std::string::npos ? shaderSrc.size() - 1 : nextLinePos));
        }

        return sources;
    }

    void OpenGLShader::compile(const std::unordered_map<GLenum, std::string> &shaderSrcs) {
        GLuint program = glCreateProgram();
        B_CORE_ASSERT(shaderSrcs.size() <= 2, "Too many shaders!");
        std::array<GLuint, 2> shaders{};
        size_t idx = 0;

        for (auto&& [type, source]: shaderSrcs) {
            GLuint shader = glCreateShader(type);
            shaders[idx] = shader;

            const auto *sourceCStr = (const GLchar *)source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                for (auto s: shaders)
                    glDeleteShader(s);

                B_CORE_ERROR("{0}", infoLog.data());
                B_CORE_ASSERT(false, "Shader compilation failure!");
                return;
            }

            glAttachShader(program, shader);
            idx++;
        }

        m_rendererID = program;
        glLinkProgram(m_rendererID);

        GLint isLinked = 0;
        glGetProgramiv(m_rendererID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_rendererID);
            for (auto s: shaders)
                glDeleteShader(s);

            B_CORE_ERROR("{0}", infoLog.data());
            B_CORE_ASSERT(false, "Shader program linking failure!");
            return;
        }

        for (auto s: shaders)
            glDetachShader(m_rendererID, s);
    }
}
