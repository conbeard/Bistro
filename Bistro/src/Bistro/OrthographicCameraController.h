//
// Created by Connor Beard on 5/9/20.
//

#ifndef BISTRO_ORTHOGRAPHICCAMERACONTROLLER_H
#define BISTRO_ORTHOGRAPHICCAMERACONTROLLER_H

#include "Bistro/Renderer/OrthographicCamera.h"
#include "Bistro/Core/Timestep.h"
#include "Bistro/Events/MouseEvent.h"
#include "Bistro/Events/ApplicationEvent.h"

namespace Bistro {

    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void onUpdate(Timestep ts);
        void onEvent(Event& event);

        OrthographicCamera& getCamera() { return m_camera; }
        const OrthographicCamera& getCamera() const { return m_camera; }

    private:
        bool onMouseScrolled(MouseScrolledEvent& event);
        bool onWindowResized(WindowResizeEvent& event);
    private:
        float m_aspectRatio, m_zoom = 1.0f;
        OrthographicCamera m_camera;

        bool m_rotation;
        glm::vec3 m_cameraPosition;
        float m_cameraRotation = 0.0f, m_cameraSpeed = 2.0f;
    };
}

#endif //BISTRO_ORTHOGRAPHICCAMERACONTROLLER_H
