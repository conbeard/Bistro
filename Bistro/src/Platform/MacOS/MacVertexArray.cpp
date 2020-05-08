//
// Created by Connor Beard on 5/7/20.
//

#include "MacVertexArray.h"

namespace Bistro {
    MacVertexArray::MacVertexArray() : _impl(new MacVertexArrayImpl()) {}

    MacVertexArray::~MacVertexArray() {
        if (_impl) { delete _impl; _impl = nullptr; }
    }

    void MacVertexArray::bind() const {
        _impl->bind();
    }

    void MacVertexArray::unbind() const {
        _impl->unbind();
    }

    void MacVertexArray::addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {

    }

    void MacVertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {

    }
}
