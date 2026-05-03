#include <memory>
#include <glm/glm.hpp>
#include "triangle.hpp"

Triangle::Triangle() {

    position = glm::vec3();
    angle = 0;
    transform.position = position;
    transform.rotation = angle;


    mesh->vertices = {
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
         0.0f,  0.5f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,   0.0f, 0.0f, 1.0f
    };
    mesh->vertex_count = 3;
    mesh->indices = {
        0, 1, 2
    };
    mesh->add(0, 2);
    mesh->add(1, 3);

    shader->vertex_source = "#version 330 core\n"
                            "layout (location = 0) in vec2 aPos;\n"
                            "layout (location = 1) in vec3 aColor;\n"
                            "out vec3 vColor;\n"
                            "void main()\n"
                            "{\n"
                            "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                            "   vColor = aColor;\n"
                            "}\0";
                            
    shader->fragment_source = "#version 330 core\n"
                              "in vec3 vColor;\n"
                              "out vec4 FragColor;\n"
                              "void main()\n"
                              "{\n"
                              "   FragColor = vec4(vColor, 1.0f);\n"
                              "}\n\0";
}
