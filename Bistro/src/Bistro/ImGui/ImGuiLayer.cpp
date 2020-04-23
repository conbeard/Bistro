//
// Created by Connor Beard on 4/22/20.
//

#include "bpch.h"
#include "ImGuiLayer.h"

#include "Core.h"
#include "Bistro/Log.h"
#include "Bistro/Events/Event.h"
#include "Bistro/Events/KeyEvent.h"

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Bistro/Application.h>
#include "Platform/OpenGL/imgui_impl_opengl3.h"

namespace Bistro {

    ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer") {}
    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;


        // Temporary, use Bistro keycodes
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

//        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach() {

    }

    void ImGuiLayer::onUpdate() {
        Application& app = Application::get();
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());
        io.DisplayFramebufferScale = ImVec2(2, 2);

        auto time = (float) glfwGetTime();
        io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event &event) {
        EventDispatcher dispatcher(event);

        dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT_FN(ImGuiLayer::onKeyTyped));
        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::onKeyPressed));
        dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::onKeyReleased));

        dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::onMouseMoved));
        dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::onMouseScrolled));
        dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::onMouseButtonPressed));
        dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::onMouseButtonReleased));

        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::onWindowResize));
    }

    bool ImGuiLayer::onKeyPressed(KeyPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.getKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::onKeyReleased(KeyReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.getKeyCode()] = false;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::onMouseButtonPressed(MouseButtonPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.getMouseButton()] = true;
        B_CORE_INFO("{0}", event);
        return false;
    }

    bool ImGuiLayer::onMouseButtonReleased(MouseButtonReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.getMouseButton()] = false;
        return false;
    }

    bool ImGuiLayer::onMouseMoved(MouseMovedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(event.getX(), event.getY());
        return false;
    }

    bool ImGuiLayer::onMouseScrolled(MouseScrolledEvent& event) {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseWheelH += event.getXOffset();
        io.MouseWheel += event.getYOffset();
        return false;
    }

    bool ImGuiLayer::onKeyTyped(KeyTypedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        if (event.getKeyCode() > 0 && event.getKeyCode() < 0x10000)
            io.AddInputCharacter((unsigned short)event.getKeyCode());
        return false;
    }


    bool ImGuiLayer::onWindowResize(WindowResizeEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)event.getWidth(), (float)event.getHeight());
        io.DisplayFramebufferScale = ImVec2(2, 2);
        glViewport(0, 0, event.getWidth(), event.getHeight());

        return false;
    }

}
