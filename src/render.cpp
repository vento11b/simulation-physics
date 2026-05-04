#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "window.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "loader.hpp"
#include "triangle.hpp"

int width = 800, height = 600;

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


Camera camera;
int main() {
    Window window(width, height);
    window.init();
    window.use();
    window.loadGlad();
    
    glViewport(0, 0, width, height); 
    glClearColor(0.2f, 0.3f, 0.3f, 5.0f);
    
    glfwSetMouseButtonCallback(window.window, mouse_button_callback);
    glfwSetCursorPosCallback(window.window, cursor_position_callback);
    glfwSetFramebufferSizeCallback(window.window, framebuffer_size_callback);
    
    
    Loader loader;
    Triangle t;
    loader.load(&t);

    camera.position = glm::vec2(0,0);
    camera.speed = 1.0f;
    while(!glfwWindowShouldClose(window.window) && !glfwWindowShouldClose(window.window)) {
        glfwPollEvents();    
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 view = camera.getView();
        glm::mat4 projection = glm::ortho(
            0.0f, (float)width,
            0.0f, (float)height
        );
        t.draw(view, projection);

        glfwSwapBuffers(window.window);
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height) {
    width = _width;
    height = _height;
    glViewport(0, 0, width, height);
}

static bool dragging = 0;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        dragging = (action == GLFW_PRESS);
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
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

    camera.position.x -= dx*camera.speed;
    camera.position.y += dy*camera.speed;

}
