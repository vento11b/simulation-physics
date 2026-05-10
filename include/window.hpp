#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.hpp"

class Window {
public:
    GLFWwindow* glwindow;
    Camera* camera;
    int width, height;

    Window(int _width, int _height, Camera* _camera = new Camera{glm::vec2(0), 1.0f});

    int init();
    void use();
    int loadGlad();

    static void framebuffer_size_callback(GLFWwindow* glwindow, int _width, int _height);
    static void cursor_position_callback(GLFWwindow* glwindow, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* glwindow, double xoffset, double yoffset);
    static void mouse_button_callback(GLFWwindow* glwindow, int button, int action, int mods);
};