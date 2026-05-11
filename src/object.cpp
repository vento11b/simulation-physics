#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "object.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "shader.hpp"


static float default_vertices[3][2] = {{-0.5f, -0.5f},
                                        {0.0f,  0.5f}, 
                                        {0.5f, -0.5f}};

static unsigned int default_indices[3] = {0,1,2};

Mesh Object::default_mesh = Mesh(default_vertices, 3, default_indices, 3);

Shader Object::default_vertex_shader(GL_VERTEX_SHADER, "./shaders/default_vertex.glsl");
Shader Object::default_fragment_shader(GL_FRAGMENT_SHADER, "./shaders/default_fragment.glsl");
Shader Object::default_shader = Shader({&default_vertex_shader, &default_fragment_shader});


void Object::draw(Window window) {
    mesh->load();
    shader->use();

    glm::mat4 model =  glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    model =            glm::rotate(model, rotation, glm::vec3(0,0,1));
    model =            glm::scale(model, glm::vec3(scale, 0.0f));
    glm::mat4 view = window.camera->getView();
    glm::mat4 projection = glm::ortho(  -window.width  / 2.0f / window.camera->zoom,
                                         window.width  / 2.0f / window.camera->zoom,
                                        -window.height / 2.0f / window.camera->zoom,
                                         window.height / 2.0f / window.camera->zoom);
    
    shader->setVec3("color", color);
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
}

void Object::draw(glm::mat4& view, glm::mat4& projection) {
    shader->use();

    glm::mat4 model =  glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    model =            glm::rotate(model, rotation, glm::vec3(0,0,1));
    model =            glm::scale(model, glm::vec3(scale, 0.0f));

    shader->setVec3("color", color);
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
}

void Object::draw() {
    shader->use();

    glBindVertexArray(mesh->VAO);
    glDrawElements(mesh->type, mesh->vertex_count, GL_UNSIGNED_INT, 0);
}