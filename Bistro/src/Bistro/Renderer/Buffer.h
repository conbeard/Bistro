//
// Created by Connor Beard on 4/25/20.
//

#ifndef BISTRO_BUFFER_H
#define BISTRO_BUFFER_H

#include "Bistro/Core/Core.h"
#include "Bistro/Core/Log.h"

namespace Bistro {

    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t shaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            default:
            case ShaderDataType::None:
                B_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
        }
    }

    struct BufferElement {
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized) {}

        uint32_t getComponentCount() const {
            switch (type) {
                default:
                case ShaderDataType::None:
                    B_CORE_ASSERT(false, "Unknown ShaderDataType!");
                    return 0;
                case ShaderDataType::Float:
                    return 1;
                case ShaderDataType::Float2:
                    return 2;
                case ShaderDataType::Float3:
                    return 3;
                case ShaderDataType::Float4:
                    return 4;
                case ShaderDataType::Mat3:
                    return 9;
                case ShaderDataType::Mat4:
                    return 16;
                case ShaderDataType::Int:
                    return 1;
                case ShaderDataType::Int2:
                    return 2;
                case ShaderDataType::Int3:
                    return 3;
                case ShaderDataType::Int4:
                    return 4;
                case ShaderDataType::Bool:
                    return 1;
            }
        }
    };

    class BufferLayout {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_elements(elements) {
            calculateOffsetsAndStride();
        }

        inline const std::vector<BufferElement>& getElements() const { return m_elements; }
        inline uint32_t getStride() const { return m_stride; }

        std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
    private:
        void calculateOffsetsAndStride() {
            for (auto& ele : m_elements) {
                ele.offset = m_stride;
                m_stride += ele.size;
            }
        }

    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& getLayout() = 0;

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
