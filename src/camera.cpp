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

void Camera::mouse_button_callback(int button, int action, int mods) {

    //std::printf("%f, %f\n", self->position.x, self->position.y);
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        dragging = (action == GLFW_PRESS);
    }

}

void Camera::scroll_callback(double xoffset, double yoffset) {
    if (yoffset > 0)
        zoom *= 1.1f;
        
    else
        zoom /= 1.1f;
    //std::printf("%lf\n", yoffset);

}

void Camera::cursor_position_callback(double xpos, double ypos) {
    static double lastx;
    static double lasty;
    if (!dragging) {
        lastx = xpos;
        lasty = ypos;
        return;
    }
    float dx = xpos - lastx;
    float dy = ypos - lasty;

    lastx = xpos;
    lasty = ypos;

    position.x -= dx*speed / zoom;
    position.y += dy*speed / zoom;

}
