//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_OPENGLBUFFER_H
#define BISTRO_OPENGLBUFFER_H

#include "bpch.h"
#include "Bistro/Renderer/Buffer.h"

namespace Bistro {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        void bind() const override;
        void unbind() const override;

        inline void setLayout(const BufferLayout& layout) override { m_layout = layout; }
        inline const BufferLayout& getLayout() override { return m_layout; }

    private:
        uint32_t m_rendererID;
        BufferLayout m_layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
        ~OpenGLIndexBuffer() override;

        void bind() const override;
        void unbind() const override;

        uint32_t getCount() const override { return m_count; };

    private:
        uint32_t m_count;
        uint32_t m_rendererID;
    };
}

#endif //BISTRO_OPENGLBUFFER_H
