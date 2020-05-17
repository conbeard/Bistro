//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_ENTRYPOINT_H
#define BISTRO_ENTRYPOINT_H

#include "Bistro.h"

extern Bistro::Application* Bistro::CreateApplication();

int main(int argc, char** argv) {
    Bistro::Log::Init();
    B_CORE_INFO("Welcome to Bistro!");

    B_PROFILE_BEGIN_SESSION("Startup", "BistroProfile-startup.json");
    auto app = Bistro::CreateApplication();
    B_PROFILE_END_SESSION();

    B_PROFILE_BEGIN_SESSION("Runtime", "BistroProfile-runtime.json");
    app->Run();
    B_PROFILE_END_SESSION();

    B_PROFILE_BEGIN_SESSION("Shutdown", "BistroProfile-shutdown.json");
    delete app;
    B_PROFILE_END_SESSION();
}


#endif //BISTRO_ENTRYPOINT_H
