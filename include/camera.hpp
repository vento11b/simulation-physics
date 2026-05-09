#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    glm::vec2 position;
    float zoom = 1;
    float speed;
    bool dragging;
    glm::mat4 getView();
    Camera(glm::vec2 _position, float _speed) : position(_position), speed(_speed) {};
    static void cursor_position_callback(GLFWwindow* wwindow, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* wwindow, double xoffset, double yoffset);
    static void mouse_button_callback(GLFWwindow* wwindow, int button, int action, int mods);
};