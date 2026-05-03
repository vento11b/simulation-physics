#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    GLFWwindow* window;
    int width, height;

    Window(int width, int height);

    int init();
    void use();
    int loadGlad();
};