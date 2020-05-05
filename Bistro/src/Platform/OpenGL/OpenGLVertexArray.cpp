//
// Created by Connor Beard on 4/26/20.
//

#include "bpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Bistro {


    static GLenum shaderDataTypeToGLBaseType(ShaderDataType type) {
        switch (type) {
            default:
            case ShaderDataType::None:
            B_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_FLOAT;
            case ShaderDataType::Bool:
                return GL_BOOL;
        }
        return 0;
    }



    OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &m_rendererID);
    }

    void OpenGLVertexArray::bind() const {
        glBindVertexArray(m_rendererID);
    }

    void OpenGLVertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
        B_CORE_ASSERT(!vertexBuffer->getLayout().getElements().empty(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_rendererID);
        vertexBuffer->bind();


        uint32_t index = 0;
        const auto& layout = vertexBuffer->getLayout();
        for (const auto& ele: layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                    index,
                    ele.getComponentCount(),
                    shaderDataTypeToGLBaseType(ele.type),
                    ele.normalized ? GL_TRUE : GL_FALSE,
                    layout.getStride(),
                    (const void*) ele.offset
            );
            index++;
        }
        m_vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
        glBindVertexArray(m_rendererID);
        indexBuffer->bind();
        m_indexBuffer = indexBuffer;
    }
}
