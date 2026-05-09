#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.hpp"

class Window {
public:
    GLFWwindow* window;
    Camera* camera;
    int width, height;

    Window(int _width, int _height, Camera* _camera = new Camera{glm::vec2(0), 1.0f});

    int init();
    void use();
    int loadGlad();
    static void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);
};