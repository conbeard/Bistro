//
// Created by Connor Beard on 4/24/20.
//

#ifndef BISTRO_GRAPHICSCONTEXT_H
#define BISTRO_GRAPHICSCONTEXT_H

namespace Bistro {

    class GraphicsContext {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };
}

#endif //BISTRO_GRAPHICSCONTEXT_H
