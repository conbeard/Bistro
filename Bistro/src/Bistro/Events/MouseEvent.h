//
// Created by Connor Beard on 4/21/20.
//

#ifndef BISTRO_MOUSEEVENT_H
#define BISTRO_MOUSEEVENT_H

#include "bpch.h"
#include "Event.h"

namespace Bistro {

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y)
            : m_mouseX(x), m_mouseY(y) {}

        inline float getX() const { return m_mouseX; }
        inline float getY() const { return m_mouseY; }


        std::string toString() const override {
            std::stringstream ss;
            ss << "Mouse Moved Event: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_mouseX, m_mouseY;
    };


    class MouseButtonEvent : public Event {
    public:
        inline int getMouseButton() const { return m_button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput)
    protected:
        MouseButtonEvent(int button) : m_button(button) {}

        int m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int button)
                : MouseButtonEvent(button) {}


        std::string toString() const override {
            std::stringstream ss;
            ss << "Mouse Button Pressed Event: " << m_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };


    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int button)
                : MouseButtonEvent(button) {}


        std::string toString() const override {
            std::stringstream ss;
            ss << "Mouse Button Released Event: " << m_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased )
    };


    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
                : m_xOffset(xOffset), m_yOffset(yOffset) {}

        inline float getXOffset() const { return m_xOffset; }
        inline float getYOffset() const { return m_yOffset; }


        std::string toString() const override {
            std::stringstream ss;
            ss << "Mouse Scrolled Event: " << m_xOffset << ", " << m_yOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_xOffset, m_yOffset;
    };
}

#endif //BISTRO_MOUSEEVENT_H
