#pragma once
#include "window.hpp"
#include <ui/imgui.h>
#include <ui/backends/imgui_impl_glfw.h>
#include <ui/backends/imgui_impl_opengl3.h>

struct Ui {
    Ui(Window* window);
    void init();
    Window* window;
    ImGuiIO io;
};
