//
// Created by Connor Beard on 4/22/20.
//

#ifndef BISTRO_IMGUILAYER_H
#define BISTRO_IMGUILAYER_H

#include <Bistro/Events/KeyEvent.h>
#include <Bistro/Events/MouseEvent.h>
#include <Bistro/Events/ApplicationEvent.h>
#include "Bistro/Layer.h"

namespace Bistro {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach();
        void onDetach();
        void onUpdate();
        void onEvent(Event& event);

    private:
        bool onMouseButtonPressed(MouseButtonPressedEvent& event);
        bool onMouseButtonReleased(MouseButtonReleasedEvent& event);
        bool onMouseMoved(MouseMovedEvent& event);
        bool onMouseScrolled(MouseScrolledEvent& event);

        bool onKeyPressed(KeyPressedEvent& event);
        bool onKeyReleased(KeyReleasedEvent& event);
        bool onKeyTyped(KeyTypedEvent& event);

        bool onWindowResize(WindowResizeEvent& event);

        float m_time = 0.0f;
    };

}

#endif //BISTRO_IMGUILAYER_H
