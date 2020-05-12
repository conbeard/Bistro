//
// Created by Connor Beard on 4/26/20.
//

#ifndef BISTRO_VERTEXARRAY_H
#define BISTRO_VERTEXARRAY_H

#include "Buffer.h"

namespace Bistro {

    class VertexArray {
    public:
        virtual ~VertexArray() = default;;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

        static Ref<VertexArray> create();

    };

}


#endif //BISTRO_VERTEXARRAY_H
