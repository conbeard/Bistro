//
// Created by Connor Beard on 5/6/20.
//

#include "bpch.h"
#include "OpenGLTexture.h"

#include "Bistro/Core/Core.h"
#include "Bistro/Core/Log.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Bistro {

    OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : m_path(path) {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        B_CORE_ASSERT(data, "Failed to load Texture2D");

        GLenum format = channels == 4 ? GL_RGBA : GL_RGB;

        m_width = width;
        m_height = height;

        glGenTextures(1, &m_rendererID);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_rendererID);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_rendererID);
    }
}
