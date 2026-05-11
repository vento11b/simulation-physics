#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "entitysystem.hpp"

struct InstanceType {
    glm::mat4 model;
    glm::vec3 color;
};

template <typename InstanceType>
class Batch {
public:
    Mesh* mesh;
    Shader* shader;
    unsigned int instanceVBO;
    std::vector<InstanceType> instances;

    Batch(Object* object)
        : mesh(object->mesh), shader(object->shader) {
            object->mesh->load();
            object->shader->use();
        }
   
    Batch(Mesh* mesh, Shader* shader)
        : mesh(mesh), shader(shader) {
            mesh->load();
            shader->use();
        }

    void addInstance(InstanceType instanceData) {
        instances.push_back(instanceData);
    }

    void updateInstanceBuffer() {
        if (instanceVBO == 0) {
            glGenBuffers(1, &instanceVBO);
        }
        glBindVertexArray(mesh->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(InstanceType), instances.data(), GL_DYNAMIC_DRAW);
        
        // Model matrix (mat4 = 4 vec4)
        //for (int i = 0; i < 4; ++i) {
        //    glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceType), (void*)(sizeof(float) * i * 4));
        //    glEnableVertexAttribArray(1 + i);
        //    glVertexAttribDivisor(1 + i, 1);
        //}
        
        // Position
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceType), (void*)(sizeof(float) * 4));
        glEnableVertexAttribArray(1);
        glVertexAttribDivisor(1, 1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Color
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceType), (void*)(sizeof(float) * 6));
        glEnableVertexAttribArray(2);
        glVertexAttribDivisor(2, 1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw(Window& window) {
        shader->use();
        glm::mat4 view = window.camera->getView();
        glm::mat4 projection = glm::ortho(
            -window.width / 2.0f / window.camera->zoom,
             window.width / 2.0f / window.camera->zoom,
            -window.height / 2.0f / window.camera->zoom,
             window.height / 2.0f / window.camera->zoom);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        glBindVertexArray(mesh->VAO);
        glDrawElementsInstanced(mesh->type, mesh->index_count, GL_UNSIGNED_INT, 0, instances.size());
        glBindVertexArray(0);
    }
};
