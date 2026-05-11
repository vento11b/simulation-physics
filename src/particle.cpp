#include <cstdio>
#include <cmath>
#include <vector>
#include "particle.hpp"

Particle::Particle(glm::vec2 _position, float _radius, float _rotation, glm::vec<3, unsigned char> _color, int _divisions, Shader* _shader) {
    divisions = _divisions;
    
    position = glm::vec2(_position);
    rotation = _rotation;
    scale = glm::vec2(_radius);
    radius = _radius;
    color = glm::vec<3, char>(_color);

    mesh->vertex_count = divisions+1;
    mesh->index_count = divisions*3;
    
    mesh->vertices = new float[mesh->vertex_count][2];
    mesh->indices = new unsigned int[mesh->index_count];

    float _vertex[2] = {0.0f, 0.0f};
    memcpy(mesh->vertices[0], &_vertex, 2 * sizeof(float));
    //std::printf("%f, %f\n", _vertex[0], _vertex[0]);
    
    float angle_gap = (2*M_PI)/divisions;
    for (int i = 0; i < divisions; i++) {
        float _vertex[2] = {(float)(0.5f*cos(i*angle_gap)),  (float)(0.5f*sin(i*angle_gap))};
        memcpy(mesh->vertices[i+1], &_vertex, 2 * sizeof(float));
        
        //std::printf("%f, %f\n", _vertex[0], _vertex[1]);
    }

    for (unsigned int i = 1; i < divisions; i++) {
        unsigned int _index[3] = {0, i, i+1};
        memcpy(mesh->indices+(i-1)*3, &_index, 3 * sizeof(unsigned int));
    }
    
    unsigned int _index[3] = {0, (unsigned int)divisions, 1};
    memcpy(mesh->indices + (divisions-1)*3, &_index, 3 * sizeof(unsigned int));

    shader=_shader;
}

