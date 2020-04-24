 //
// Created by Connor Beard on 4/23/20.
//

#ifndef BISTRO_MACINPUT_H
#define BISTRO_MACINPUT_H

#include "Bistro/Input.h"

namespace Bistro {

    class MacInput : public Input {
    protected:
        virtual bool isKeyPressedImpl(int keycode) override;

        virtual bool isMouseButtonPressedImpl(int keycode) override;
        virtual std::pair<float, float> getMousePosImpl() override;
        virtual float getMouseXImpl() override;
        virtual float getMouseYImpl() override;
    };
}

#endif //BISTRO_MACINPUT_H
