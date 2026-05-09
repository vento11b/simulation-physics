#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.hpp"

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
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(width, height, "Simulation", NULL, NULL);
    if (window == NULL) {
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
    //glViewport(0, 0, width, height);

    return 0;
}

void Window::use(){
    glfwMakeContextCurrent(window);
}

void Window::framebuffer_size_callback(GLFWwindow* wwindow, int _width, int _height) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(wwindow));
    //std::printf("aAAAa");
    self->width = _width;
    self->height = _height;
    glViewport(0, 0, _width, _height);
}