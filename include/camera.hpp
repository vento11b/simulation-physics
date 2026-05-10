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
    void cursor_position_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);
    void mouse_button_callback(int button, int action, int mods);
};