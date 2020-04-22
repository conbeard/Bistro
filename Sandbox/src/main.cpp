//
// Created by Connor Beard on 4/20/20.
//

#include <Bistro.h>

class ExampleLayer : public Bistro::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void onUpdate() override {
//        B_TRACE("Example Layer Update");
    }

    void onEvent(Bistro::Event& e) override {
        B_TRACE("{0}", e);
    }
};

class Sandbox : public Bistro::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
    }

    ~Sandbox() override {
        B_INFO("Sandbox Destructor!");
    }
};

Bistro::Application* Bistro::CreateApplication() {
    return new Sandbox();
}
