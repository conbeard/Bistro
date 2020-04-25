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

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onImGuiRender() override;

        void begin();
        void end();
    private:
        float m_time = 0.0f;
    };

}

#endif //BISTRO_IMGUILAYER_H
