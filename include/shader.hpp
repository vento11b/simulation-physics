#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct shader_program {
    unsigned int type;
    FILE* file = NULL;
    const char* source;
    //shader_program(unsigned int _type, const char* _source) : type(_type), source(_source) {};
};

struct Shader {
    std::vector<Shader> sub_shaders;
    unsigned int program;

    unsigned int type;
    FILE* file = NULL;
    const char* source;
    void use();
    int compile();
    int link();
    void setMat4(const char* name, glm::mat4& m);

    Shader() {};
    Shader(unsigned int _type, const char* _source) : type(_type), source(_source) {};
    Shader(std::vector<Shader> _sub_shaders) : sub_shaders(_sub_shaders) {};
    Shader(Shader _sub_shaders[]) {sub_shaders.insert(sub_shaders.end(), _sub_shaders);};
    Shader(Shader &_sub_shader) {sub_shaders.push_back(_sub_shader);};

};