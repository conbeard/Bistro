//
// Created by Connor Beard on 4/20/20.
//

#ifndef BISTRO_ENTRYPOINT_H
#define BISTRO_ENTRYPOINT_H

#include "Bistro.h"

extern Bistro::Application* Bistro::CreateApplication();

int main(int argc, char** argv) {
    Bistro::Log::Init();
    auto logger = Bistro::Log::GetBistroLogger();
    logger->info("Welcome to Bistro");

    auto app = Bistro::CreateApplication();
    app->Run();
    delete app;
}


#endif //BISTRO_ENTRYPOINT_H
