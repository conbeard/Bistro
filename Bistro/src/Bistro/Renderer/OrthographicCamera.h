//
// Created by Connor Beard on 4/27/20.
//

#ifndef BISTRO_ORTHOGRAPHICCAMERA_H
#define BISTRO_ORTHOGRAPHICCAMERA_H

#include <glm/glm.hpp>

namespace Bistro {

    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void setPosition(const glm::vec3& pos) { m_position = pos; recalculateViewMatrix(); }
        void setRotation(float rot) { m_rotation = rot; recalculateViewMatrix(); }

        const glm::vec3& getPosition() const { return m_position; }
        float getRotation() const { return m_rotation; }
        const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
        const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }
    private:
        void recalculateViewMatrix();
    private:
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_viewProjectionMatrix;

        glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
        float m_rotation = 0.0f;
    };
}

#endif //BISTRO_ORTHOGRAPHICCAMERA_H
