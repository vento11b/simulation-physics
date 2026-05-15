#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ui/imgui.h>
#include <ui/backends/imgui_impl_glfw.h>
#include <ui/backends/imgui_impl_opengl3.h>

#include "window.hpp"
#include "camera.hpp"

Window::Window(int _width, int _height, Camera* _camera) {
    camera = _camera;
    width = _width;
    height = _height;
}
int Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_SAMPLES, 16);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    

    
    glwindow = glfwCreateWindow(width, height, "Simulation", NULL, NULL);
    if (glwindow == NULL) {
        std::printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    
    return 0;
}
int Window::loadGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::printf("Failed to initialize GLAD\n");
        return -1;
    }
    glViewport(0, 0, width, height);

    return 0;
}

void Window::use(){
    glfwMakeContextCurrent(glwindow);
}

void Window::framebuffer_size_callback(GLFWwindow* glwindow, int _width, int _height) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(glwindow));
    
    //std::printf("aAAAa");
    self->width = _width;
    self->height = _height;
    glViewport(0, 0, _width, _height);
}

void Window::cursor_position_callback(GLFWwindow* glwindow, double xpos, double ypos) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(glwindow));

    ImGui_ImplGlfw_CursorPosCallback(glwindow, xpos, ypos);
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;
    self->camera->cursor_position_callback(xpos, ypos);
}
void Window::scroll_callback(GLFWwindow* glwindow, double xoffset, double yoffset) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(glwindow));

    ImGui_ImplGlfw_ScrollCallback(glwindow, xoffset, yoffset);
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;
    self->camera->scroll_callback(xoffset, yoffset);
}
void Window::mouse_button_callback(GLFWwindow* glwindow, int button, int action, int mods) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(glwindow));

    ImGui_ImplGlfw_MouseButtonCallback(glwindow, button, action, mods);
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;
    self->camera->mouse_button_callback(button, action, mods);
}