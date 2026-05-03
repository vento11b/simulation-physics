#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "window.hpp"
#include "object.hpp"
#include "loader.hpp"
#include "triangle.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    Window window(800, 600);
    window.init();
    window.use();
    window.loadGlad();
    
    glViewport(0, 0, 800, 600); 
    glClearColor(0.2f, 0.3f, 0.3f, 5.0f);
    


    
    
    Loader loader;
    Triangle t;
    loader.load(&t);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(!glfwWindowShouldClose(window.window) && !glfwWindowShouldClose(window.window)) {
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        t.draw();

        glfwSwapBuffers(window.window);
        glfwPollEvents();    
    }

    glfwTerminate();

    return 0;
}

void init(){

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

