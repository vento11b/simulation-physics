#pragma once
#include "glad/glad.h"

struct Mesh {
    Mesh(float (*_vertices)[2], unsigned int _vertex_count, unsigned int* _indices, unsigned int _index_count, GLenum _type = GL_TRIANGLES) : vertices(_vertices), vertex_count(_vertex_count), indices(_indices), index_count(_index_count), type(_type), loaded(false) {};
    void load();
    float (*vertices)[2];
    unsigned int* indices;
    GLenum  type;
    unsigned int vertex_count;
    unsigned int index_count;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    bool loaded;
};
