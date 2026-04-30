#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "polygon.h"


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::printf("Failed to initialize GLAD\n");
        return -1;
    }  

    glViewport(0, 0, 800, 600);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < triangle.count; i++) {
            glVertex2f(triangle.vertices[i].x, triangle.vertices[i].y);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();

    return 0;
}