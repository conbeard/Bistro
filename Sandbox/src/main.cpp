//
// Created by Connor Beard on 4/20/20.
//

#include <Bistro.h>

class Sandbox : public Bistro::Application {
public:
    Sandbox() {
        B_INFO("Sandbox Init!");
    }

    ~Sandbox() override {
        B_INFO("Sandbox Destructor!");
    }
};

Bistro::Application* Bistro::CreateApplication() {
    return new Sandbox();
}
