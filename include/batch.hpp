#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "entitysystem.hpp"

struct InstanceData {
    glm::mat4 model;
    glm::vec3 color;
};

class Batch {
public:
    Mesh* mesh;
    Shader* shader;
    GLuint instanceVBO = 0;
    std::vector<InstanceData> instances;

    Batch(Object* object)
        : mesh(object->mesh), shader(object->shader) {
            EntitySystem::load(object);
        }

    void addInstance(const glm::mat4& model, const glm::vec3& color) {
        instances.push_back({model, color});
    }

    void updateInstanceBuffer() {
        if (instanceVBO == 0) {
            glGenBuffers(1, &instanceVBO);
        }
        glBindVertexArray(mesh->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(InstanceData), instances.data(), GL_DYNAMIC_DRAW);
        // Model matrix (mat4 = 4 vec4)
        for (int i = 0; i < 4; ++i) {
            glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(float) * i * 4));
            glEnableVertexAttribArray(1 + i);
            glVertexAttribDivisor(1 + i, 1);
        }
        // Color
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(float) * 16));
        glEnableVertexAttribArray(5);
        glVertexAttribDivisor(5, 1);
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
