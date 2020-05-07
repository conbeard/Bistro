//
// Created by Connor Beard on 5/6/20.
//

#ifndef BISTRO_OPENGLTEXTURE_H
#define BISTRO_OPENGLTEXTURE_H

#include "Bistro/Renderer/Texture.h"

namespace Bistro {

    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        uint32_t getWidth() const override { return m_width; }
        uint32_t getHeight() const override { return m_height; }

        void bind(uint32_t slot) const override;

    private:
        std::string m_path;
        uint32_t m_width, m_height;
        uint32_t m_rendererID;
    };
}

#endif //BISTRO_OPENGLTEXTURE_H
