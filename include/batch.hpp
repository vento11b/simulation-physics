#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "mesh.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "object.hpp"

struct Model {
        Model(glm::vec2 _position, glm::vec2 _scale, float _rotation, bool _hasPosition, bool _hasScale, bool _hasRotation) {
            position = _position;
            scale = _scale;
            rotation = _rotation;
            hasPosition = _hasPosition;
            hasScale = _hasScale;
            hasRotation = _hasRotation;
        }
        glm::vec2 position{0};
        glm::vec2 scale{100};
        float rotation{0};

        bool hasPosition=0;
        bool hasScale=0;
        bool hasRotation=0;
    };

struct InstanceStruct {
    glm::mat4 model;
    glm::vec<3, unsigned int> color;
};

//template <typename InstanceType>
class Batch {
public:
    Mesh* mesh;
    Shader* shader;
    unsigned int instanceVBO;
    std::vector<InstanceStruct> instances;

    Batch(Object* object, Model model)
        : mesh(object->mesh), shader(object->shader) {
            object->mesh->load();
            object->shader->use();
        }
   
    //Batch(Mesh* mesh, Shader* shader)
    //    : mesh(mesh), shader(shader) {
    //        mesh->load();
    //        shader->use();
    //    }

    void addInstance(InstanceStruct instanceData) {
        
        instances.push_back(InstanceStruct());
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
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceStruct), (void*)(sizeof(float) * 16));
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
