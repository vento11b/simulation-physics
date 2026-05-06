f#include <cstdio>
#include <cmath>
#include "circle.hpp"

Circle::Circle(glm::vec2 _position, glm::vec2 _scale, float _rotation, int _divisions) {
    divisions = _divisions;
    
    model.position = glm::vec2(_position);
    model.rotation = _rotation;
    model.scale = glm::vec2(_scale);
    
    mesh->add(0, 2);
    mesh->add(1, 3);

    mesh->vertex_count = divisions+1;

    mesh->vertices.insert(mesh->vertices.end(), {0.0f, 0.0f,   0.0f, 0.0f, 1.0f});


    float angle_gap = (2*M_PI)/divisions;
    std::printf("%f\n", angle_gap);
    for (int i = 0; i < divisions; i++) {
        mesh->vertices.insert(mesh->vertices.end(), {
            (float)(0.5f*cos(i*angle_gap)),  (float)(0.5f*sin(i*angle_gap)),   0.0f, 0.0f, 1.0f
        });
    }
    
    for (unsigned int i = 1; i < divisions; i++) {
        mesh->indices.insert(mesh->indices.end(), {
            0, i, i+1
        });
    }
    mesh->indices.insert(mesh->indices.end(), {
        0, (unsigned int)divisions, 1
    });

    //shader->sub_shaders.push_back(Shader(GL_VERTEX_SHADER, "./shaders/default_vertex_circle.glsl"));
    //                        
    //shader->sub_shaders.push_back(Shader(GL_FRAGMENT_SHADER, "./shaders/default_fragment_circle.glsl"));
}

//Shader Circle::default_vertex_shader(GL_VERTEX_SHADER, "./shaders/default_vertex_circle.glsl");
//Shader Circle::default_fragment_shader(GL_FRAGMENT_SHADER, "./shaders/default_fragment_circle.glsl");
Shader Circle::default_shader({Shader(GL_VERTEX_SHADER, "./shaders/default_vertex_circle.glsl"), Shader(GL_FRAGMENT_SHADER, "./shaders/default_fragment_circle.glsl")});
Shader a({Shader(), Shader()})