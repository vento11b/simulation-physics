#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

enum class shader_type {
    vertex = GL_VERTEX_SHADER,
    fragment = GL_FRAGMENT_SHADER,
    geometry = GL_GEOMETRY_SHADER
};


typedef struct {
    unsigned int location;
    int size;
    GLenum type;
    bool normalized;
    size_t offset;
} VertexAttribute;

typedef struct {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int vertex_count;
    
    unsigned int VAO;
    unsigned int VBO;
    
    void add(unsigned int location, int size);
    void applyLayout();

    std::vector<VertexAttribute> attributes;
    size_t stride;
} Mesh;

typedef struct {
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;

    glm::mat4 getMatrix();
} Model;


typedef struct {
    shader_type type;
    const char *vertex_source;
    const char *fragment_source;
    unsigned int shader;

    void use();

    void setMat4(const char* name, glm::mat4& m);
} Shader;

class Object {
public:
    Model model;
    Mesh* mesh;
    Shader* shader;

    Object();
    void draw(glm::mat4& view, glm::mat4& projection);
    void draw();
};