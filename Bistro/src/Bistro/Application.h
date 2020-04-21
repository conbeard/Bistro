//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_APPLICATION_H
#define BISTRO_APPLICATION_H

#include "Core.h"

namespace Bistro {
    class Application {
        public:
            Application();
            virtual ~Application();
            static void Run();
    };

    // To be implemented in client
    Application* CreateApplication();
}

#endif //BISTRO_APPLICATION_H
