//
// Created by Connor Beard on 5/7/20.
//

#ifndef BISTRO_MACVERTEXARRAYINTERFACE_H
#define BISTRO_MACVERTEXARRAYINTERFACE_H

namespace Bistro {
    class MacVertexArrayImpl {
    public:
        MacVertexArrayImpl();
        ~MacVertexArrayImpl();

        void init();
        void bind() const;
        void unbind() const;

//        void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
//        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer);
//
//        const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const;
//        const Ref<IndexBuffer>& getIndexBuffer() const;

    private:
        void* self;
    };
}

#endif //BISTRO_MACVERTEXARRAYINTERFACE_H
