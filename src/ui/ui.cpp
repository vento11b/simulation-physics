#include "ui/ui.hpp"
#include "window.hpp"
#include <ui/imgui.h>
#include <ui/backends/imgui_impl_glfw.h>
#include <ui/backends/imgui_impl_opengl3.h>

Ui::Ui(Window* _window) {
    window = _window;
}

void Ui::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    io = ImGui::GetIO(); (void)io;
    // estilo opcional
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->glwindow, true);
    // usa GLSL version según tu OpenGL
    ImGui_ImplOpenGL3_Init("#version 330");
}