#include <glad/glad.h>
#include <cstdio>
#include "entitysystem.hpp"
#include "window.hpp"
#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void EntitySystem::load() {
    for (Object *object : entities) {
        if (object->mesh->loaded) continue;
        glGenVertexArrays(1, &object->mesh->VAO);
        glGenBuffers(1, &object->mesh->VBO);
        glGenBuffers(1, &object->mesh->EBO);
        
        glBindVertexArray(object->mesh->VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, object->mesh->VBO);
        glBufferData(GL_ARRAY_BUFFER, 2 * object->mesh->vertex_count * sizeof(float), object->mesh->vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->mesh->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * object->mesh->index_count * sizeof(unsigned int), object->mesh->indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
        object->mesh->loaded = true;
    }
}

void EntitySystem::draw(Window window) {
    for (Object *object : entities) object->draw(window);
}

void EntitySystem::draw() {
    for (Object *object : entities) object->draw();
}