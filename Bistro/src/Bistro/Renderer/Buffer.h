//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_BUFFER_H
#define BISTRO_BUFFER_H

namespace Bistro {

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static VertexBuffer* create(float* vertices, uint32_t size);
    };


    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        static IndexBuffer* create(uint32_t* indices, uint32_t count);
    };
}

#endif //BISTRO_BUFFER_H
