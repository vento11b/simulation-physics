#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "object.hpp"


glm::mat4 Model::getMatrix() {
    glm::mat4 matrix =  glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    matrix =            glm::rotate(matrix, rotation, glm::vec3(0,0,1));
    matrix =            glm::scale(matrix, glm::vec3(scale, 0.0f));
    return matrix;
}

void Mesh::add(unsigned int location, int size) {
    VertexAttribute attr;
    attr.location = location;
    attr.size = size;
    attr.type = GL_FLOAT;
    attr.normalized = false;
    attr.offset = stride;

    stride += size * sizeof(float);
    attributes.push_back(attr);
}

void Mesh::applyLayout() {
    for (const VertexAttribute attr : attributes) {
        glVertexAttribPointer(
            attr.location,
            attr.size,
            attr.type,
            attr.normalized,
            stride,
            (void*)attr.offset
        );

        glEnableVertexAttribArray(attr.location);
    }
}


void Shader::use() {
    glUseProgram(shader);
}

void Shader::setMat4(const char* name, glm::mat4& m) {
    glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, &m[0][0]);
}

Object::Object() {
    mesh = new Mesh;
    shader = new Shader;
}

void Object::draw(glm::mat4& view, glm::mat4& projection) {
    shader->use();

    glm::mat4 matrix_model = model.getMatrix();

    shader->setMat4("model", matrix_model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glBindVertexArray(mesh->VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
}

void Object::draw() {
    shader->use();

    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->vertex_count, GL_UNSIGNED_INT, 0);
}