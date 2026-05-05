#include <cstdio>
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
            0.5f*cos(i*angle_gap),  0.5f*sin(i*angle_gap),   0.0f, 0.0f, 1.0f
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

    shader->sub_shaders.push_back(Shader(GL_VERTEX_SHADER, "#version 330 core\n"
                            "layout (location = 0) in vec2 aPos;\n"
                            "layout (location = 1) in vec3 aColor;\n"
                            "out vec3 vColor;\n"
                            "uniform mat4 projection;\n"
                            "uniform mat4 view;\n"
                            "uniform mat4 model;\n"
                            "void main()\n"
                            "{\n"
                            "   gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                            "   vColor = aColor;\n"
                            "}\0"));
                            
    shader->sub_shaders.push_back(Shader(GL_FRAGMENT_SHADER, "#version 330 core\n"
                              "in vec3 vColor;\n"
                              "out vec4 FragColor;\n"
                              "void main()\n"
                              "{\n"
                              "   FragColor = vec4(vColor, 1.0f);\n"
                              "}\n\0"));
}