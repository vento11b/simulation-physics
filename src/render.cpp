#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "window.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "loader.hpp"
#include "circle.hpp"
#include "triangle.hpp"

#include <iostream>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}


int width = 800, height = 600;

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


Camera camera(glm::vec2(0,0), 1.0f);
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

    Circle c1(glm::vec2(400, 300), glm::vec2(50), 20);
    loader.load(&c1);
    c1.shader->compile();
    c1.shader->link();


    //std::cout << c1.mesh->vertices << "\n";
    //std::cout << c1.mesh->indices << "\n";

    while(!glfwWindowShouldClose(window.window) && !glfwWindowShouldClose(window.window)) {
        glfwPollEvents();    
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 view = camera.getView();
        glm::mat4 projection = glm::ortho(
            0.0f, (float)width,
            0.0f, (float)height
        );
        
        c1.draw(view, projection);

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
