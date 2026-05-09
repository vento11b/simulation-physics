#include "camera.hpp"
#include "window.hpp"
#include <glad/glad.h>
#include <cstdio>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getView() {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position, 0));
}

void Camera::mouse_button_callback(GLFWwindow* wwindow, int button, int action, int mods) {
    Camera* self = static_cast<Camera*>(static_cast<Window*>(glfwGetWindowUserPointer(wwindow))->camera);

    //std::printf("%f, %f\n", self->position.x, self->position.y);
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        self->dragging = (action == GLFW_PRESS);
    }
}

void Camera::scroll_callback(GLFWwindow* wwindow, double xoffset, double yoffset) {
    Camera* self = static_cast<Camera*>(static_cast<Window*>(glfwGetWindowUserPointer(wwindow))->camera);
    if (yoffset > 0)
        self->zoom *= 1.1f;
        
    else
        self->zoom /= 1.1f;
    //std::printf("%lf\n", yoffset);

}

void Camera::cursor_position_callback(GLFWwindow* wwindow, double xpos, double ypos) {
    Camera* self = static_cast<Camera*>(static_cast<Window*>(glfwGetWindowUserPointer(wwindow))->camera);

    static double lastx;
    static double lasty;
    if (!self->dragging) {
        lastx = xpos;
        lasty = ypos;
        return;
    }
    float dx = xpos - lastx;
    float dy = ypos - lasty;

    lastx = xpos;
    lasty = ypos;

    self->position.x -= dx*self->speed / self->zoom;
    self->position.y += dy*self->speed / self->zoom;

}
