#pragma once
#include "object.hpp"

struct Loader {

    int load_mesh(Mesh *mesh);
    int load_shader(Shader *shader);
    int load(Object *object);


    unsigned int load_mesh(float *vertices);
    unsigned int load_shader(const char* vertex_source, const char* fragment_source);
};