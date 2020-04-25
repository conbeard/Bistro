//
// Created by Connor Beard on 4/22/20.
//

#ifndef BISTRO_LAYERSTACK_H
#define BISTRO_LAYERSTACK_H

#include "bpch.h"
#include "Core.h"
#include "Layer.h"

namespace Bistro {

    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popLayer(Layer* layer);
        void popOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_layers.end(); }

    private:
        std::vector<Layer*> m_layers;
        unsigned int m_layerInsertIndex = 0;
    };

}

#endif //BISTRO_LAYERSTACK_H
