#include <iostream>
#include <cstdio>

#include <random>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "circle.hpp"
#include "entitysystem.hpp"


float randomf(float min, float max);

void print_vec2_array(float (*v)[2], unsigned int count)
{
    for (unsigned int i = 0; i < count; i++) {
        printf("[%u] x: %f, y: %f\n", i, v[i][0], v[i][1]);
    }
}

void print_uints(const unsigned int* p, unsigned int n)
{
    for (unsigned int i = 0; i < n; i++) {
        printf("[%u] = %u\n", i, p[i]);
    }
}

int main() {
    Window window(1600, 1000);
    window.init();
    window.use();
    window.loadGlad();

    
    glViewport(0, 0, window.width, window.height); 
    glClearColor(0.2f, 0.3f, 0.3f, 5.0f);
    
    
    glfwSetWindowUserPointer(window.window,  &window);
    glfwSetMouseButtonCallback(window.window, Camera::mouse_button_callback);
    glfwSetCursorPosCallback(window.window, Camera::cursor_position_callback);
    glfwSetScrollCallback(window.window, Camera::scroll_callback);

    glfwSetFramebufferSizeCallback(window.window, Window::framebuffer_size_callback);
    
    std::srand(std::time(0));


    EntitySystem es;

    //es.entities.push_back(new Object(glm::vec2{0}, glm::vec2{100}, 0.0f, glm::vec3{0, 256, 0}));
    //es.entities.push_back(new Circle());
    
    //print_vec2_array(es.entities[0]->mesh->vertices, es.entities[0]->mesh->vertex_count);
    //std::printf("%s\n", es.entities[0]->shader->sub_shaders[0]->source);
    //print_uints(es.entities[0]->mesh->indices, es.entities[0]->mesh->index_count);
    //std::printf("%d, %d, %d\n", es.entities[0]->color.x, es.entities[0]->color.y, es.entities[0]->color.z);
    
    //for (int i = 0; i<100000; i++) {
    //    es.entities.insert(es.entities.end(), {new Object(  glm::vec2(randomf(-window.width/2, window.width/2), randomf(-window.height/2, window.height/2)),
    //                                                        glm::vec2(randomf(1, 10)),
    //                                                        randomf(0, 360),
    //                                                        glm::vec3(randomf(0,256), randomf(0, 256), randomf(0, 256)))});
    //}
    es.entities.reserve(10000);
    for (int i = 0; i<10000; i++) {
        es.entities.insert(es.entities.end(), {new Circle(  glm::vec2(randomf(-window.width/2, window.width/2), randomf(-window.height/2, window.height/2)),
                                                            //glm::vec2(randomf(1, 10)),
                                                            glm::vec2(10),
                                                            glm::vec3((unsigned int)randomf(0,256), (unsigned int)randomf(0, 256), (unsigned int)randomf(0, 256)),
                                                            25  )});
    }
    
    es.load();

    while(!glfwWindowShouldClose(window.window) && !glfwWindowShouldClose(window.window)) {
        glfwPollEvents();    
        glClear(GL_COLOR_BUFFER_BIT);
        
        //std::printf("%d, %d\n", window.width, window.height);
        es.draw(window);

        glfwSwapBuffers(window.window);
    }

    glfwTerminate();

    return 0;
}

float randomf(float min, float max) {
    float r = (float)rand() / ((float)RAND_MAX + 1.0f);

    return min + r * (max - min);
}

