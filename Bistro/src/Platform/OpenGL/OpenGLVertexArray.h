//
// Created by Connor Beard on 4/26/20.
//

#ifndef BISTRO_OPENGLVERTEXARRAY_H
#define BISTRO_OPENGLVERTEXARRAY_H

#include "Bistro/Renderer/VertexArray.h"

namespace Bistro {

    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override = default;

        void bind() const override;
        void unbind() const override;

        void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return m_vertexBuffers; }
        const Ref<IndexBuffer>& getIndexBuffer() const override { return m_indexBuffer; }

    private:
        uint32_t m_rendererID;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };
}

#endif //BISTRO_OPENGLVERTEXARRAY_H
