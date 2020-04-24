//
// Created by Connor Beard on 4/21/20.
//

#ifndef BISTRO_WINDOW_H
#define BISTRO_WINDOW_H

#include <utility>

#include "bpch.h"

#include "Bistro/Core.h"
#include "Bistro/Events/Event.h"

namespace Bistro {

    struct WindowProps {
        std::string m_title;
        unsigned int m_width, m_height;

        WindowProps(
            std::string  title = "Bistro",
            unsigned int width = 1280,
            unsigned int height = 720
        ) : m_title(std::move(title)), m_width(width), m_height(height) {}
    };


    class Window {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() = default;

        virtual void onUpdate() = 0;

        virtual unsigned int getHeight() const = 0;
        virtual unsigned int getWidth() const = 0;

        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;

        virtual void* getNativeWindow() const = 0;

        static Window* create(const WindowProps& props = WindowProps());
    };

};

#endif //BISTRO_WINDOW_H
