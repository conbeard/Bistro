//
// Created by Connor Beard on 4/20/20.
//

#include <Bistro.h>
#include <iostream>

class Sandbox : public Bistro::Application {
public:
    Sandbox() {
        auto logger = Bistro::Log::GetClientLogger();
        logger->info("Sandbox Init");
    }

    ~Sandbox() override {
        std::cout << "example destructor\n";
    }
};

Bistro::Application* Bistro::CreateApplication() {
    return new Sandbox();
}
