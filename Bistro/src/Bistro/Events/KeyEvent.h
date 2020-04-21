//
// Created by Connor Beard on 4/21/20.
//

#ifndef BISTRO_KEYEVENT_H
#define BISTRO_KEYEVENT_H

#include "bpch.h"
#include "Event.h"

namespace Bistro {

    class KeyEvent : public Event {
    public:
        inline int getKeyCode() const { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(int keyCode) : m_keyCode(keyCode) {}

        int m_keyCode;
    };


    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

        inline int getRepeatCount() const { return m_repeatCount; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "Key Pressed Event: " << m_keyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_repeatCount;
    };


    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}


        std::string toString() const override {
            std::stringstream ss;
            ss << "Key Released Event: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

}

#endif //BISTRO_KEYEVENT_H
