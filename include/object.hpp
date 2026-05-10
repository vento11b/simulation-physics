#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "window.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "mesh.hpp"

struct Object {
    Object(glm::vec2 _position, glm::vec2 _scale, float _rotation, glm::vec3 _color, Mesh* _mesh, Shader* _shader) : position(_position), scale(_scale), rotation(_rotation), color(_color), mesh(_mesh), shader(_shader) {};

    Object(glm::vec2 _position, glm::vec2 _scale, float _rotation) : Object(_position, _scale, _rotation, glm::vec<3, unsigned char>{0, 0, 255}, &default_mesh, &default_shader) {};
    Object(glm::vec2 _position, glm::vec2 _scale, float _rotation, glm::vec3 _color) : Object(_position, _scale, _rotation, _color, &default_mesh, &default_shader) {};
    Object(Mesh* _mesh, Shader* _shader) : Object(glm::vec2{400.0f, 300.0f}, glm::vec2{200.0f}, 0.0f, glm::vec<3, unsigned char>{0, 0, 255}, _mesh, _shader) {};
    Object() : Object(glm::vec2{400.0f, 300.0f}, glm::vec2{200.0f}, 0.0f, glm::vec<3, unsigned char>{0, 0, 255}, &default_mesh, &default_shader) {};

    void draw(glm::mat4& view, glm::mat4& projection);
    void draw(Window window);
    void draw();

    Mesh* mesh = NULL;
    Shader* shader = NULL;

    glm::vec2 position{400.0f, 300.0f};
    glm::vec2 scale{200.0f};
    float rotation = 0.0f;
    glm::vec<3, unsigned char> color{0, 0, 256};
    glm::vec2 velocity{0.0f};

    static Mesh default_mesh;
    static Shader default_shader;
};