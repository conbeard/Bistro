//
// Created by Connor Beard on 5/7/20.
//

#ifndef BISTRO_MACVERTEXARRAY_H
#define BISTRO_MACVERTEXARRAY_H

#include "Bistro/Renderer/VertexArray.h"
#include "MacVertexArrayInterface.h"

namespace Bistro {
    class MacVertexArray : public VertexArray {
    public:
        MacVertexArray();
        virtual ~MacVertexArray();

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
    private:
        MacVertexArrayImpl* _impl;
    };
}

#endif //BISTRO_MACVERTEXARRAY_H
