#include <iostream>
#include <cstdio>
#include <random>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ui/imgui.h>
#include <ui/backends/imgui_impl_glfw.h>
#include <ui/backends/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ui/ui.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "object.hpp"
#include "circle.hpp"
#include "entitysystem.hpp"
#include "batch.hpp"

void print_uints(const unsigned int *p, unsigned int n);

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
    
    Ui ui(&window);
    ui.init();

    
    glViewport(0, 0, window.width, window.height); 
    glClearColor(0.2f, 0.3f, 0.3f, 5.0f);
    
    
    glfwSetWindowUserPointer(window.glwindow,  &window);

    glfwSetMouseButtonCallback(window.glwindow, Window::mouse_button_callback);
    glfwSetCursorPosCallback(window.glwindow, Window::cursor_position_callback);
    glfwSetScrollCallback(window.glwindow, Window::scroll_callback);
    glfwSetFramebufferSizeCallback(window.glwindow, Window::framebuffer_size_callback);
    
    std::srand(std::time(0));


    EntitySystem es;
    
    Circle tempCircle;
    Mesh* circleMesh = tempCircle.mesh;
    Shader* circleShader = tempCircle.shader;

    Batch circleBatch(circleMesh, circleShader);
    es.load(&tempCircle);
    // Agrega instancias (puedes usar tu bucle actual)
    for (int i = 0; i < 1'000'000; ++i) {
        glm::vec2 pos = glm::vec2(randomf(-100'000, 100'000), randomf(-100'000, 100'000));
        glm::vec2 scale = glm::vec2(100);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));
        model = glm::scale(model, glm::vec3(scale, 0.0f));
        glm::vec3 color = glm::vec3(randomf(0,256), randomf(0,256), randomf(0,256));
        circleBatch.addInstance(model, color);
    }
    circleBatch.updateInstanceBuffer();
    
    
    
    double last_time = glfwGetTime();

    int frames = 0;
    double fps = 0.0;
    while(!glfwWindowShouldClose(window.glwindow) && !glfwWindowShouldClose(window.glwindow)) {
        frames++;

    double current = glfwGetTime();
    double elapsed = current - last_time;

    if (elapsed >= 1.0)
    {
        fps = frames / elapsed;

        frames = 0;
        last_time = current;
    }
        glfwPollEvents();    
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        
        ImGui::Begin("Test");
        //ImGui::ShowMetricsWindow();
        ImGui::Text("FPS: %.1f", fps);
        if (ImGui::Button("Click me")) {
            printf("CLICK!\n");
        }
        //render = !render;
        //if (render) es.draw(window);

        circleBatch.draw(window);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.glwindow);
    }

    glfwTerminate();

    return 0;
}

float randomf(float min, float max) {
    float r = (float)rand() / ((float)RAND_MAX + 1.0f);

    return min + r * (max - min);
}

