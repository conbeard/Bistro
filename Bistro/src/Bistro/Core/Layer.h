//
// Created by Connor Beard on 4/22/20.
//

#ifndef BISTRO_LAYER_H
#define BISTRO_LAYER_H

#include "Bistro/Core/Core.h"
#include "Bistro/Events/Event.h"
#include "Bistro/Core/Timestep.h"

namespace Bistro {

    class Layer {
    public:
        Layer(const std::string& name="Layer");
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Timestep ts) {}
        virtual void onImGuiRender() {}
        virtual void onEvent(Event& event) {}

        inline const std::string& getName() const { return m_debugName; }
    protected:
        std::string m_debugName;
    };
}

#endif //BISTRO_LAYER_H
