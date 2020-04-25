//
// Created by Connor Beard on 4/24/20.
//

#ifndef BISTRO_OPENGLCONTEXT_H
#define BISTRO_OPENGLCONTEXT_H

#include <GLFW/glfw3.h>
#include "Bistro/Renderer/GraphicsContext.h"


namespace Bistro {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void init() override;
        void swapBuffers() override;

    private:
        GLFWwindow* m_windowHandle;
    };
}

#endif //BISTRO_OPENGLCONTEXT_H
