#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <cstdio>

//#include <cstdio>

struct shader_program {
    unsigned int type;
    const char* file = NULL;
    const char* source;
    //shader_program(unsigned int _type, const char* _source) : type(_type), source(_source) {};
};

struct Shader {
    std::vector<Shader*> sub_shaders;
    unsigned int program;

    unsigned int type;
    const char* filename = NULL;
    const char* source = NULL;
    bool linked = false;
    void use();
    int compile();
    int link();
    void setMat4(const char* name, glm::mat4& m);
    void setVec3(const char* name, glm::vec<3, unsigned char>& v);
    void add_shader(Shader* _sub_shader);

    Shader() {};
    //Shader(unsigned int _type, const char* _source) : type(_type), source(_source) {};
    Shader(unsigned int _type, const char* _filename);
    Shader(std::vector<Shader*> _sub_shaders);
    
    //Shader(Shader _sub_shaders[]) {sub_shaders.insert(sub_shaders.end(), _sub_shaders);};
    Shader(Shader* _sub_shader);

};