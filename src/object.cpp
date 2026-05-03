#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "object.hpp"


glm::mat4 Transform::getMatrix() {
    glm::mat4 transformation =  glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    transformation =            glm::rotate(transformation, rotation, glm::vec3(0,0,1));
    transformation =            glm::scale(transformation, glm::vec3(scale, 0.0f));
    return transformation;
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

    glm::mat4 model = transform.getMatrix();

    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glBindVertexArray(mesh->VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
}

void Object::draw() {
    shader->use();

    //glm::mat4 model = transform.getMatrix();

    //shader->setMat4("model", model);

    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->vertex_count, GL_UNSIGNED_INT, 0);
    //9 std::printf("%d\n", mesh->vertex_count);
}