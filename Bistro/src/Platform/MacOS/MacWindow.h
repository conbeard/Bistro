//
// Created by Connor Beard on 4/21/20.
//

#ifndef BISTRO_MACWINDOW_H
#define BISTRO_MACWINDOW_H

#include "Bistro/Core/Window.h"
#include "Bistro/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Bistro {

    class MacWindow : public Window {
    public:
        MacWindow(const WindowProps& props);
        virtual ~MacWindow();

        void onUpdate() override;

        virtual unsigned int getWidth() const override { return m_data.width; }
        virtual unsigned int getHeight() const override { return m_data.height; }

        inline void setEventCallback(const EventCallbackFn& callback) override { m_data.callback = callback; }
        void setVSync(bool enabled) override;
        bool isVSync() const override;

        inline virtual void* getNativeWindow() const override { return m_window; }
    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

        GLFWwindow* m_window;
        GraphicsContext* m_context;

        struct WindowData {
            std::string title;
            unsigned int width, height;
            bool vSync;

            EventCallbackFn callback;
        } m_data;
    };
}

#endif //BISTRO_MACWINDOW_H
