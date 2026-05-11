#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "object.hpp"

struct InstanceStruct {
    glm::mat4 model;
    glm::vec<3, unsigned char> color;
};

class Batch {
public:
    Mesh* mesh;
    Shader* shader;
    Object* object;
    glm::vec2 scale{2.8e-15f};
    float rotation{0};
    unsigned int instanceVBO = 0;
    std::vector<InstanceStruct> instances;

    //Batch(Object* object, Model _model)
    //    : mesh(object->mesh), shader(object->shader), model(_model) {
    //        object->mesh->load();
    //        object->shader->use();
    //    }
   
    Batch(Mesh* mesh, Shader* shader)
        : mesh(mesh), shader(shader){
            mesh->load();
            shader->use();
        }

    void addInstance(const glm::mat4& model, const glm::vec<3, unsigned char>& color) {
        InstanceStruct idata;
        idata.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
        idata.model = glm::rotate(idata.model, 0.0f, glm::vec3(0,0,1));
        idata.model = glm::scale(idata.model, glm::vec3(100.0f));
        idata.color = glm::vec<3, unsigned char>{255,0,0};
        instances.push_back({model, color});
    }

    void addInstance(glm::vec2 position, glm::vec<3, unsigned char> color) {
        glm::mat4 model{glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))};
        model = glm::rotate(model, rotation, glm::vec3(0,0,1));
        model = glm::scale(model, glm::vec3(scale, 0));
        instances.push_back({model, color});
    }

    void updateInstanceBuffer() {
        if (instanceVBO == 0) {
            glGenBuffers(1, &instanceVBO);
        }
        glBindVertexArray(mesh->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(InstanceStruct), instances.data(), GL_DYNAMIC_DRAW);
        
        // Model matrix (mat4 = 4 vec4)
        for (int i = 0; i < 4; ++i) {
            glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceStruct), (void*)(sizeof(float) * i * 4));
            glEnableVertexAttribArray(1 + i);
            glVertexAttribDivisor(1 + i, 1);
        }
        
        // Position
        //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceType), (void*)(sizeof(float) * 4));
        //glEnableVertexAttribArray(1);
        //glVertexAttribDivisor(1, 1);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);

        // Color
        glVertexAttribPointer(5, 3, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(InstanceStruct), (void*)(sizeof(float) * 16));
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
