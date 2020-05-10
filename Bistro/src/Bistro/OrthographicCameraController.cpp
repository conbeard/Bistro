//
// Created by Connor Beard on 5/9/20.
//

#include "bpch.h"
#include "OrthographicCameraController.h"

#include "Bistro/Input.h"
#include "Bistro/KeyCodes.h"
#include "Bistro/MouseButtonCodes.h"

namespace Bistro {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_aspectRatio(aspectRatio), m_rotation(rotation), m_cameraPosition(0.0f),
        m_camera(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom) {

    }

    void OrthographicCameraController::onUpdate(Timestep ts) {

        // WASD QE Camera controls
        if (Input::isKeyPressed(B_KEY_A))
            m_cameraPosition.x -= m_cameraSpeed * ts;
        if (Input::isKeyPressed(B_KEY_D))
            m_cameraPosition.x += m_cameraSpeed * ts;
        if (Input::isKeyPressed(B_KEY_S))
            m_cameraPosition.y -= m_cameraSpeed * ts;
        if (Input::isKeyPressed(B_KEY_W))
            m_cameraPosition.y += m_cameraSpeed * ts;
        if (m_rotation && Input::isKeyPressed(B_KEY_Q))
            m_cameraRotation += m_cameraSpeed * ts;
        if (m_rotation && Input::isKeyPressed(B_KEY_E))
            m_cameraRotation -= m_cameraSpeed * ts;

        m_camera.setPosition(m_cameraPosition);
        m_camera.setRotation(m_cameraRotation);

        m_cameraSpeed = m_zoom;
    }

    void OrthographicCameraController::onEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
    }

    bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent &event) {
        m_zoom -= event.getYOffset() * 0.5f;
        m_zoom = std::max(m_zoom, 0.25f);
        m_camera.setProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);
        return false;
    }

    bool OrthographicCameraController::onWindowResized(WindowResizeEvent &event) {
        m_aspectRatio = (float) event.getWidth() / (float) event.getHeight();
        m_camera.setProjection(-m_aspectRatio * m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom);
        return false;
    }
}
